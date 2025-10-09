// Copyright (c) 2017-2023, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#include "slate/slate.hh"
#include "internal/internal.hh"

#include <cstdio>


namespace slate {

namespace impl {

//------------------------------------------------------------------------------
/// @internal
/// Distributed parallel Hermitian rank k update.
/// Generic implementation for any target.
/// Dependencies enforce the following behavior:
/// - bcast communications are serialized,
/// - herk operations are serialized,
/// - bcasts can get ahead of herks by the value of lookahead.
/// Note A and C are passed by value, so we can transpose if needed
/// (for uplo = Upper) without affecting caller.
/// @ingroup herk_impl
///
template <Target target, typename scalar_t>
void herk(
    blas::real_type<scalar_t> alpha, Matrix<scalar_t> A,
    blas::real_type<scalar_t> beta,  HermitianMatrix<scalar_t> C,
    Options const& opts )
{
    using real_t = blas::real_type<scalar_t>;
    using BcastList = typename Matrix<scalar_t>::BcastList;
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    // Assumes column major
    const Layout layout = Layout::ColMajor;

    // Options
    int64_t lookahead = get_option<int64_t>( opts, Option::Lookahead, 1 );

    // if upper, change to lower
    if (C.uplo() == Uplo::Upper)
        C = conj_transpose( C );

    // A is mt-by-nt, C is mt-by-mt
    assert(A.mt() == C.mt());

    // OpenMP needs pointer types, but vectors are exception safe
    std::vector<uint8_t> bcast_vector(A.nt());
    std::vector<uint8_t>  gemm_vector(A.nt());
    uint8_t* bcast = bcast_vector.data();
    uint8_t* gemm  =  gemm_vector.data();
    SLATE_UNUSED( bcast ); // Used only by OpenMP
    SLATE_UNUSED( gemm  ); // Used only by OpenMP

    const int priority_0 = 0;
    const int queue_0 = 0;

    if (target == Target::Devices) {
        C.allocateBatchArrays();
        C.reserveDeviceWorkspace();
    }

    // set min number for omp nested active parallel regions
    slate::OmpSetMaxActiveLevels set_active_levels( MinOmpActiveLevels );

#pragma omp parallel
#pragma omp master
{
    int64_t nt = A.nt();
    int64_t mt = A.mt();
    int64_t la = lookahead;
    std::vector<std::vector<MPI_Request>> col_reqs(nt);

    int64_t first_post = std::min<int64_t>(nt, la);
    for (int64_t k = 0; k < first_post; ++k) {
        BcastList bcast_list;
        for (int64_t i = 0; i < mt; ++i)
            bcast_list.push_back({i, k, {C.sub(i, i, 0, i), C.sub(i, C.mt()-1, i, i)}});
        col_reqs[k] = A.template listIbcast<target>(bcast_list, layout);
    }

    for (int64_t k = 0; k < nt; ++k) {

        int64_t post_k = k + la;
        if (post_k < nt) {
            BcastList bcast_list;
            for (int64_t i = 0; i < mt; ++i)
                bcast_list.push_back({i, post_k, {C.sub(i, i, 0, i), C.sub(i, C.mt()-1, i, i)}});
            col_reqs[post_k] = A.template listIbcast<target>(bcast_list, layout);
        }

        #pragma omp task firstprivate(k) depend(in:col_reqs[k])
        {
            if (!col_reqs[k].empty()) {
                slate_mpi_call(MPI_Waitall(static_cast<int>(col_reqs[k].size()), col_reqs[k].data(), MPI_STATUSES_IGNORE));
            }

            internal::herk<target>(
                alpha,
                A.sub(0, mt-1, k, k),
                (k == 0 ? beta : real_t(1.0)),
                std::move(C),
                priority_0, queue_0, layout
            );

            auto A_colblock = A.sub(0, mt-1, k, k);
            A_colblock.releaseRemoteWorkspace();
            A_colblock.releaseLocalWorkspace();
        }
    }

    #pragma omp taskwait
    C.tileUpdateAllOrigin();
}

    C.clearWorkspace();
}

} // namespace impl

//------------------------------------------------------------------------------
/// Distributed parallel Hermitian rank k update.
/// Performs the Hermitian rank k operation
/// \[
///     C = \alpha A A^H + \beta C,
/// \]
/// where alpha and beta are scalars, C is an n-by-n Hermitian
/// matrix, and A is an n-by-k matrix.
/// The matrices can be conjugate-transposed beforehand, e.g.,
///
///     auto AT = slate::conj_transpose( A );
///     slate::herk( alpha, AT, beta, C );
///
/// Complexity (in real): $\approx k n^{2}$ flops.
///
//------------------------------------------------------------------------------
/// @tparam scalar_t
///         One of float, double, std::complex<float>, std::complex<double>.
//------------------------------------------------------------------------------
/// @param[in] alpha
///         The real scalar alpha.
///
/// @param[in] A
///         The n-by-k matrix A.
///
/// @param[in] beta
///         The real scalar beta.
///
/// @param[in,out] C
///         On entry, the n-by-n Hermitian matrix C.
///         On exit, overwritten by the result
///         $C = \alpha A A^H + \beta C$.
///
/// @param[in] opts
///         Additional options, as map of name = value pairs. Possible options:
///         - Option::Lookahead:
///           Number of blocks to overlap communication and computation.
///           lookahead >= 0. Default 1.
///         - Option::Target:
///           Implementation to target. Possible values:
///           - HostTask:  OpenMP tasks on CPU host [default].
///           - HostNest:  nested OpenMP parallel for loop on CPU host.
///           - HostBatch: batched BLAS on CPU host.
///           - Devices:   batched BLAS on GPU device.
///
/// @ingroup herk
///
template <typename scalar_t>
void herk(
    blas::real_type<scalar_t> alpha, Matrix<scalar_t>& A,
    blas::real_type<scalar_t> beta,  HermitianMatrix<scalar_t>& C,
    Options const& opts )
{
    Target target = get_option( opts, Option::Target, Target::HostTask );

    switch (target) {
        case Target::Host:
        case Target::HostTask:
            impl::herk<Target::HostTask>( alpha, A, beta, C, opts );
            break;
        case Target::HostNest:
            impl::herk<Target::HostNest>( alpha, A, beta, C, opts );
            break;
        case Target::HostBatch:
            impl::herk<Target::HostBatch>( alpha, A, beta, C, opts );
            break;
        case Target::Devices:
            impl::herk<Target::Devices>( alpha, A, beta, C, opts );
            break;
    }
}

//------------------------------------------------------------------------------
// Explicit instantiations.
template
void herk<float>(
    float alpha, Matrix<float>& A,
    float beta,  HermitianMatrix<float>& C,
    Options const& opts);

template
void herk<double>(
    double alpha, Matrix<double>& A,
    double beta,  HermitianMatrix<double>& C,
    Options const& opts);

template
void herk< std::complex<float> >(
    float alpha, Matrix< std::complex<float> >& A,
    float beta,  HermitianMatrix< std::complex<float> >& C,
    Options const& opts);

template
void herk< std::complex<double> >(
    double alpha, Matrix< std::complex<double> >& A,
    double beta,  HermitianMatrix< std::complex<double> >& C,
    Options const& opts);

} // namespace slate
