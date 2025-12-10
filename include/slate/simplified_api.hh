// Copyright (c) 2017-2023, University of Tennessee. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause
// This program is free software: you can redistribute it and/or modify it under
// the terms of the BSD 3-Clause license. See the accompanying LICENSE file.

#ifndef SLATE_SIMPLIFIED_API_HH
#define SLATE_SIMPLIFIED_API_HH

namespace slate {

//------------------------------------------------------------------------------
/// @defgroup multiply Matrix-matrix multiplication routines
/// @brief Simplified interface for matrix-matrix products
///
/// These functions provide a simplified interface to BLAS-3 matrix-matrix 
/// multiplication routines, automatically dispatching to the appropriate
/// underlying function (gemm, hemm, symm, etc.) based on matrix types.
///
/// @{

//-----------------------------------------
/// Matrix-matrix multiply: \( C = \alpha A B + \beta C \)
///
/// Band matrix times general matrix.
///
/// @param[in] alpha
///     Scalar multiplier for A*B product
///
/// @param[in] A
///     Band matrix operand
///
/// @param[in] B
///     General matrix operand
///
/// @param[in] beta
///     Scalar multiplier for C
///
/// @param[in,out] C
///     On entry, the matrix C. On exit, overwritten by \( \alpha A B + \beta C \)
///
/// @param[in] opts
///     Additional options (target, lookahead, etc.)
///
/// @ingroup multiply
///
template <typename scalar_t>
void multiply(
    scalar_t alpha, BandMatrix<scalar_t>& A,
                        Matrix<scalar_t>& B,
    scalar_t beta,      Matrix<scalar_t>& C,
    Options const& opts = Options())
{
    gbmm(alpha, A, B, beta, C, opts);
}

//-----------------------------------------
/// Matrix-matrix multiply: \( C = \alpha A B + \beta C \)
///
/// General matrix times general matrix (GEMM).
///
/// @param[in] alpha
///     Scalar multiplier for A*B product
///
/// @param[in] A
///     General matrix operand, m-by-k
///
/// @param[in] B
///     General matrix operand, k-by-n
///
/// @param[in] beta
///     Scalar multiplier for C
///
/// @param[in,out] C
///     On entry, m-by-n matrix. On exit, overwritten by \( \alpha A B + \beta C \)
///
/// @param[in] opts
///     Additional options:
///     - target: Target device (host, devices)
///     - lookahead: Number of blocks to lookahead (default 1)
///
/// @ingroup multiply
///
template <typename scalar_t>
void multiply(
    scalar_t alpha, Matrix<scalar_t>& A,
                    Matrix<scalar_t>& B,
    scalar_t beta,  Matrix<scalar_t>& C,
    Options const& opts = Options())
{
    gemm(alpha, A, B, beta, C, opts);
}

//-----------------------------------------
/// Hermitian band matrix multiply (left): \( C = \alpha A B + \beta C \)
///
/// @param[in] alpha Scalar multiplier
/// @param[in] A Hermitian band matrix (left operand)
/// @param[in] B General matrix
/// @param[in] beta Scalar multiplier for C
/// @param[in,out] C On exit, \( \alpha A B + \beta C \)
/// @param[in] opts Additional options
/// @ingroup multiply
///
template <typename scalar_t>
void multiply(
    scalar_t alpha, HermitianBandMatrix<scalar_t>& A,
                                 Matrix<scalar_t>& B,
    scalar_t beta,               Matrix<scalar_t>& C,
    Options const& opts = Options())
{
    hbmm(Side::Left, alpha, A, B, beta, C, opts);
}

//-----------------------------------------
/// Hermitian band matrix multiply (right): \( C = \alpha A B + \beta C \)
///
/// @param[in] alpha Scalar multiplier
/// @param[in] A General matrix
/// @param[in] B Hermitian band matrix (right operand)
/// @param[in] beta Scalar multiplier for C
/// @param[in,out] C On exit, \( \alpha A B + \beta C \)
/// @param[in] opts Additional options
/// @ingroup multiply
///
template <typename scalar_t>
void multiply(
    scalar_t alpha,              Matrix<scalar_t>& A,
                    HermitianBandMatrix<scalar_t>& B,
    scalar_t beta,               Matrix<scalar_t>& C,
    Options const& opts = Options())
{
    hbmm(Side::Right, alpha, B, A, beta, C, opts);
}

//-----------------------------------------
/// Hermitian matrix multiply (left): \( C = \alpha A B + \beta C \)
///
/// where A is Hermitian.
///
/// @param[in] alpha Scalar multiplier
/// @param[in] A Hermitian matrix (left operand)
/// @param[in] B General matrix
/// @param[in] beta Scalar multiplier for C
/// @param[in,out] C On exit, \( \alpha A B + \beta C \)
/// @param[in] opts Additional options
/// @ingroup multiply
///
template <typename scalar_t>
void multiply(
    scalar_t alpha, HermitianMatrix<scalar_t>& A,
                             Matrix<scalar_t>& B,
    scalar_t beta,           Matrix<scalar_t>& C,
    Options const& opts = Options())
{
    hemm(Side::Left, alpha, A, B, beta, C, opts);
}

//-----------------------------------------
/// Hermitian matrix multiply (right): \( C = \alpha A B + \beta C \)
///
/// where B is Hermitian.
///
/// @param[in] alpha Scalar multiplier
/// @param[in] A General matrix
/// @param[in] B Hermitian matrix (right operand)
/// @param[in] beta Scalar multiplier for C
/// @param[in,out] C On exit, \( \alpha A B + \beta C \)
/// @param[in] opts Additional options
/// @ingroup multiply
///
template <typename scalar_t>
void multiply(
    scalar_t alpha,          Matrix<scalar_t>& A,
                    HermitianMatrix<scalar_t>& B,
    scalar_t beta,           Matrix<scalar_t>& C,
    Options const& opts = Options())
{
    hemm(Side::Right, alpha, B, A, beta, C, opts);
}

//-----------------------------------------
/// Symmetric matrix multiply (left): \( C = \alpha A B + \beta C \)
///
/// where A is symmetric.
///
/// @param[in] alpha Scalar multiplier
/// @param[in] A Symmetric matrix (left operand)
/// @param[in] B General matrix
/// @param[in] beta Scalar multiplier for C
/// @param[in,out] C On exit, \( \alpha A B + \beta C \)
/// @param[in] opts Additional options
/// @ingroup multiply
///
template <typename scalar_t>
void multiply(
    scalar_t alpha, SymmetricMatrix<scalar_t>& A,
                             Matrix<scalar_t>& B,
    scalar_t beta,           Matrix<scalar_t>& C,
    Options const& opts = Options())
{
    symm(Side::Left, alpha, A, B, beta, C, opts);
}

//-----------------------------------------
/// Symmetric matrix multiply (right): \( C = \alpha A B + \beta C \)
///
/// where B is symmetric.
///
/// @param[in] alpha Scalar multiplier
/// @param[in] A General matrix
/// @param[in] B Symmetric matrix (right operand)
/// @param[in] beta Scalar multiplier for C
/// @param[in,out] C On exit, \( \alpha A B + \beta C \)
/// @param[in] opts Additional options
/// @ingroup multiply
///
template <typename scalar_t>
void multiply(
    scalar_t alpha,          Matrix<scalar_t>& A,
                    SymmetricMatrix<scalar_t>& B,
    scalar_t beta,           Matrix<scalar_t>& C,
    Options const& opts = Options())
{
    symm(Side::Right, alpha, B, A, beta, C, opts);
}

/// @}
// End of multiply group

//-----------------------------------------
// triangular_multiply()

// Left trmm
template <typename scalar_t>
void triangular_multiply(
    scalar_t alpha, TriangularMatrix<scalar_t>& A,
                              Matrix<scalar_t>& B,
    Options const& opts = Options())
{
    trmm(Side::Left, alpha, A, B, opts);
}

// Right trmm
template <typename scalar_t>
void triangular_multiply(
    scalar_t alpha,           Matrix<scalar_t>& A,
                    TriangularMatrix<scalar_t>& B,
    Options const& opts = Options())
{
    trmm(Side::Right, alpha, B, A, opts);
}

//-----------------------------------------
// triangular_solve()

// Left tbsm
template <typename scalar_t>
void triangular_solve(
    scalar_t alpha, TriangularBandMatrix<scalar_t>& A,
                                  Matrix<scalar_t>& B,
    Options const& opts = Options())
{
    tbsm(Side::Left, alpha, A, B, opts);
}

// Right tbsm
template <typename scalar_t>
void triangular_solve(
    scalar_t alpha,               Matrix<scalar_t>& A,
                    TriangularBandMatrix<scalar_t>& B,
    Options const& opts = Options())
{
    tbsm(Side::Right, alpha, B, A, opts);
}

// Left trsm
template <typename scalar_t>
void triangular_solve(
    scalar_t alpha, TriangularMatrix<scalar_t>& A,
                              Matrix<scalar_t>& B,
    Options const& opts = Options())
{
    trsm(Side::Left, alpha, A, B, opts);
}

// Right trsm
template <typename scalar_t>
void triangular_solve(
    scalar_t alpha,           Matrix<scalar_t>& A,
                    TriangularMatrix<scalar_t>& B,
    Options const& opts = Options())
{
    trsm(Side::Right, alpha, B, A, opts);
}

//-----------------------------------------
// rank_k_update()

// herk
template <typename scalar_t>
void rank_k_update(
    blas::real_type<scalar_t> alpha,          Matrix<scalar_t>& A,
    blas::real_type<scalar_t> beta,  HermitianMatrix<scalar_t>& C,
    Options const& opts = Options())
{
    herk(alpha, A, beta, C, opts);
}

// syrk
template <typename scalar_t>
void rank_k_update(
    scalar_t alpha,           Matrix<scalar_t>& A,
    scalar_t beta,   SymmetricMatrix<scalar_t>& C,
    Options const& opts = Options())
{
    syrk(alpha, A, beta, C, opts);
}

//-----------------------------------------
// rank_2k_update()

// herk
template <typename scalar_t>
void rank_2k_update(
    scalar_t alpha,                           Matrix<scalar_t>& A,
                                              Matrix<scalar_t>& B,
    blas::real_type<scalar_t> beta,  HermitianMatrix<scalar_t>& C,
    Options const& opts = Options())
{
    her2k(alpha, A, B, beta, C, opts);
}

// syrk
template <typename scalar_t>
void rank_2k_update(
    scalar_t alpha,           Matrix<scalar_t>& A,
                              Matrix<scalar_t>& B,
    scalar_t beta,   SymmetricMatrix<scalar_t>& C,
    Options const& opts = Options())
{
    syr2k(alpha, A, B, beta, C, opts);
}

//------------------------------------------------------------------------------
// Linear systems

//-----------------------------------------
// LU

//-----------------------------------------
// lu_solve()

// gbsv
template <typename scalar_t>
void lu_solve(
    BandMatrix<scalar_t>& A,
        Matrix<scalar_t>& B,
    Options const& opts = Options())
{
    Pivots pivots;
    gbsv(A, pivots, B, opts);
}

// gesv
template <typename scalar_t>
int64_t lu_solve(
    Matrix<scalar_t>& A,
    Matrix<scalar_t>& B,
    Options const& opts = Options())
{
    Pivots pivots;
    return gesv( A, pivots, B, opts );
}

//-----------------------------------------
// lu_factor()

// gbtrf
template <typename scalar_t>
void lu_factor(
    BandMatrix<scalar_t>& A, Pivots& pivots,
    Options const& opts = Options())
{
    gbtrf(A, pivots, opts);
}

// getrf
template <typename scalar_t>
int64_t lu_factor(
    Matrix<scalar_t>& A, Pivots& pivots,
    Options const& opts = Options())
{
    return getrf( A, pivots, opts );
}

//-----------------------------------------
// lu_solve_using_factor()

// gbtrs
template <typename scalar_t>
void lu_solve_using_factor(
    BandMatrix<scalar_t>& A, Pivots& pivots,
        Matrix<scalar_t>& B,
    Options const& opts = Options())
{
    gbtrs(A, pivots, B, opts);
}

// getrs
template <typename scalar_t>
void lu_solve_using_factor(
    Matrix<scalar_t>& A, Pivots& pivots,
    Matrix<scalar_t>& B,
    Options const& opts = Options())
{
    getrs(A, pivots, B, opts);
}

//-----------------------------------------
// lu_inverse_using_factor()

// In-place getri
template <typename scalar_t>
void lu_inverse_using_factor(
    Matrix<scalar_t>& A, Pivots& pivots,
    Options const& opts = Options())
{
    getri(A, pivots, opts);
}

//-----------------------------------------
// lu_inverse_using_factor_out_of_place()

// Out-of-place getri
template <typename scalar_t>
void lu_inverse_using_factor_out_of_place(
    Matrix<scalar_t>& A, Pivots& pivots,
    Matrix<scalar_t>& A_inverse,
    Options const& opts = Options())

{
    getri(A, pivots, A_inverse, opts);
}

//-----------------------------------------
// lu_rcondest_using_factor()

// gecondest
template <typename scalar_t>
blas::real_type<scalar_t> lu_rcondest_using_factor(
    Norm in_norm,
    Matrix<scalar_t>& A,
    blas::real_type<scalar_t> Anorm,
    Options const& opts = Options())
{
    return gecondest( in_norm, A, Anorm, opts );
}

//-----------------------------------------
// Cholesky

//-----------------------------------------
// chol_solve()

// pbsv
template <typename scalar_t>
void chol_solve(
    HermitianBandMatrix<scalar_t>& A,
                 Matrix<scalar_t>& B,
    Options const& opts = Options())
{
    pbsv(A, B, opts);
}

// posv
template <typename scalar_t>
int64_t chol_solve(
    HermitianMatrix<scalar_t>& A,
             Matrix<scalar_t>& B,
    Options const& opts = Options())
{
    return posv( A, B, opts );
}

// forward real-symmetric matrices to posv;
// disabled for complex
template <typename scalar_t>
int64_t chol_solve(
    SymmetricMatrix<scalar_t>& A,
             Matrix<scalar_t>& B,
    Options const& opts = Options(),
    enable_if_t< ! is_complex<scalar_t>::value >* = nullptr)
{
    return posv( A, B, opts );
}

//-----------------------------------------
// chol_factor()

// pbtrf
template <typename scalar_t>
int64_t chol_factor(
    HermitianBandMatrix<scalar_t>& A,
    Options const& opts = Options())
{
    return pbtrf( A, opts );
}

// potrf
template <typename scalar_t>
int64_t chol_factor(
    HermitianMatrix<scalar_t>& A,
    Options const& opts = Options())
{
    return potrf( A, opts );
}

// forward real-symmetric matrices to potrf;
// disabled for complex
template <typename scalar_t>
int64_t chol_factor(
    SymmetricMatrix<scalar_t>& A,
    Options const& opts = Options(),
    enable_if_t< ! is_complex<scalar_t>::value >* = nullptr)
{
    return potrf( A, opts );
}

//-----------------------------------------
// chol_solve_using_factor()

// pbtrs
template <typename scalar_t>
void chol_solve_using_factor(
    HermitianBandMatrix<scalar_t>& A,
                 Matrix<scalar_t>& B,
    Options const& opts = Options())
{
    pbtrs(A, B, opts);
}

// potrs
template <typename scalar_t>
void chol_solve_using_factor(
    HermitianMatrix<scalar_t>& A,
             Matrix<scalar_t>& B,
    Options const& opts = Options())
{
    potrs(A, B, opts);
}

// forward real-symmetric matrices to potrs;
// disabled for complex
template <typename scalar_t>
void chol_solve_using_factor(
    SymmetricMatrix<scalar_t>& A,
             Matrix<scalar_t>& B,
    Options const& opts = Options(),
    enable_if_t< ! is_complex<scalar_t>::value >* = nullptr)
{
    potrs(A, B, opts);
}

//-----------------------------------------
// chol_inverse_using_factor()

// potri
template <typename scalar_t>
void chol_inverse_using_factor(
    HermitianMatrix<scalar_t>& A,
    Options const& opts = Options())
{
    potri(A, opts);
}

//-----------------------------------------
// chol_rcondest_using_factor()

// pocondest
template <typename scalar_t>
blas::real_type<scalar_t> chol_rcondest_using_factor(
    Norm in_norm,
    HermitianMatrix<scalar_t>& A,
    blas::real_type<scalar_t> Anorm,
    Options const& opts = Options())
{
    return pocondest( in_norm, A, Anorm, opts );
}

//-----------------------------------------
// Symmetric indefinite -- block Aasen's

//-----------------------------------------
// indefinite_solve()

// hesv
template <typename scalar_t>
int64_t indefinite_solve(
    HermitianMatrix<scalar_t>& A,
             Matrix<scalar_t>& B,
    Options const& opts = Options())
{
    // auxiliary matrices
    auto H = slate::Matrix<scalar_t>::emptyLike(A);

    int64_t kl = A.tileNb(0);
    int64_t ku = A.tileNb(0);
    auto T = slate::BandMatrix<scalar_t>::emptyLike(A, kl, ku);

    Pivots pivots, pivots2;
    return hesv( A, pivots, T, pivots2, H, B, opts );
}

// forward real-symmetric matrices to hesv;
// disabled for complex
template <typename scalar_t>
int64_t indefinite_solve(
    SymmetricMatrix<scalar_t>& A,
             Matrix<scalar_t>& B,
    Options const& opts = Options(),
    enable_if_t< ! is_complex<scalar_t>::value >* = nullptr)
{
    // auxiliary matrices
    auto H = slate::Matrix<scalar_t>::emptyLike(A);

    int64_t kl = A.tileNb(0);
    int64_t ku = A.tileNb(0);
    auto T = slate::BandMatrix<scalar_t>::emptyLike(A, kl, ku);

    Pivots pivots, pivots2;
    return sysv( A, pivots, T, pivots2, H, B, opts );
}

//-----------------------------------------
// indefinite_factor()

// hetrf
template <typename scalar_t>
int64_t indefinite_factor(
    HermitianMatrix<scalar_t>& A, Pivots& pivots,
         BandMatrix<scalar_t>& T, Pivots& pivots2,
             Matrix<scalar_t>& H,
    Options const& opts = Options())
{
    return hetrf( A, pivots, T, pivots2, H, opts );
}

// forward real-symmetric matrices to hetrf;
// disabled for complex
template <typename scalar_t>
int64_t indefinite_factor(
    SymmetricMatrix<scalar_t>& A, Pivots& pivots,
         BandMatrix<scalar_t>& T, Pivots& pivots2,
             Matrix<scalar_t>& H,
    Options const& opts = Options(),
    enable_if_t< ! is_complex<scalar_t>::value >* = nullptr)
{
    return sytrf( A, pivots, T, pivots2, H, opts );
}

//-----------------------------------------
// indefinite_solve_using_factor()

// hetrs
template <typename scalar_t>
void indefinite_solve_using_factor(
    HermitianMatrix<scalar_t>& A, Pivots& pivots,
         BandMatrix<scalar_t>& T, Pivots& pivots2,
             Matrix<scalar_t>& B,
    Options const& opts = Options())
{
    hetrs(A, pivots, T, pivots2, B, opts);
}
// forward real-symmetric matrices to hetrs;
// disabled for complex
template <typename scalar_t>
void indefinite_solve_using_factor(
    SymmetricMatrix<scalar_t>& A, Pivots& pivots,
         BandMatrix<scalar_t>& T, Pivots& pivots2,
             Matrix<scalar_t>& B,
    Options const& opts = Options(),
    enable_if_t< ! is_complex<scalar_t>::value >* = nullptr)
{
    sytrs(A, pivots, T, pivots2, B, opts);
}

//------------------------------------------------------------------------------
// QR

//-----------------------------------------
// Least squares

//-----------------------------------------
// least_squares_solve()

// gels
template <typename scalar_t>
void least_squares_solve(
    Matrix<scalar_t>& A,
    Matrix<scalar_t>& BX,
    Options const& opts = Options())
{
    gels( A, BX, opts );
}

//-----------------------------------------
// QR

//-----------------------------------------
// qr_factor()

// geqrf
template <typename scalar_t>
void qr_factor(
    Matrix<scalar_t>& A, TriangularFactors<scalar_t>& T,
    Options const& opts = Options())
{
    geqrf(A, T, opts);
}

//-----------------------------------------
// qr_multiply_by_q()

// unmqr
template <typename scalar_t>
void qr_multiply_by_q(
    Side side, Op op,
    Matrix<scalar_t>& A, TriangularFactors<scalar_t>& T,
    Matrix<scalar_t>& C,
    Options const& opts = Options())
{
    unmqr(side, op, A, T, C, opts);
}

//-----------------------------------------
// LQ

//-----------------------------------------
// lq_factor()

// gelqf
template <typename scalar_t>
void lq_factor(
    Matrix<scalar_t>& A, TriangularFactors<scalar_t>& T,
    Options const& opts = Options())
{
    gelqf(A, T, opts);
}

//-----------------------------------------
// lq_multiply_by_q()

// unmlq
template <typename scalar_t>
void lq_multiply_by_q(
    Side side, Op op,
    Matrix<scalar_t>& A, TriangularFactors<scalar_t>& T,
    Matrix<scalar_t>& C,
    Options const& opts = Options())
{
    unmlq(side, op, A, T, C, opts);
}

//-----------------------------------------
// triangular_rcondest()

// trcondest
template <typename scalar_t>
blas::real_type<scalar_t> triangular_rcondest(
    Norm in_norm,
    TriangularMatrix<scalar_t>& A,
    blas::real_type<scalar_t> Anorm,
    Options const& opts = Options())
{
    return trcondest( in_norm, A, Anorm, opts );
}

//------------------------------------------------------------------------------
// Symmetric/Hermitian Eigenvalues

template <typename scalar_t>
void eig_vals(
    HermitianMatrix<scalar_t>& A,
    std::vector< blas::real_type<scalar_t> >& Lambda,
    Options const& opts = Options())
{
    Matrix<scalar_t> Z;
    heev( A, Lambda, Z, opts );
}

/// Without Z, compute only eigenvalues. Same as eig_vals.
template <typename scalar_t>
void eig(
    HermitianMatrix<scalar_t>& A,
    std::vector< blas::real_type<scalar_t> >& Lambda,
    Options const& opts = Options())
{
    eig_vals( A, Lambda, opts );
}

/// With Z, compute eigenvalues & eigenvectors.
template <typename scalar_t>
void eig(
    HermitianMatrix<scalar_t>& A,
    std::vector< blas::real_type<scalar_t> >& Lambda,
    Matrix<scalar_t>& Z,
    Options const& opts = Options())
{
    heev( A, Lambda, Z, opts );
}

//-----------------------------------------
// Real-symmetric matrices; disabled for complex
template <typename scalar_t>
void eig_vals(
    SymmetricMatrix<scalar_t>& A,
    std::vector< blas::real_type<scalar_t> >& Lambda,
    Options const& opts = Options(),
    enable_if_t< ! is_complex<scalar_t>::value >* = nullptr)
{
    Matrix<scalar_t> Z;
    syev( A, Lambda, Z, opts );
}

/// Without Z, compute only eigenvalues. Same as eig_vals.
template <typename scalar_t>
void eig(
    SymmetricMatrix<scalar_t>& A,
    std::vector< blas::real_type<scalar_t> >& Lambda,
    Options const& opts = Options(),
    enable_if_t< ! is_complex<scalar_t>::value >* = nullptr)
{
    eig_vals( A, Lambda, opts );
}

/// With Z, compute eigenvalues & eigenvectors.
template <typename scalar_t>
void eig(
    SymmetricMatrix<scalar_t>& A,
    std::vector< blas::real_type<scalar_t> >& Lambda,
    Matrix<scalar_t>& Z,
    Options const& opts = Options(),
    enable_if_t< ! is_complex<scalar_t>::value >* = nullptr)
{
    syev( A, Lambda, Z, opts );
}

//------------------------------------------------------------------------------
// Generalized symmetric/Hermitian eigenvalues

template <typename scalar_t>
void eig_vals(
    int64_t itype,
    HermitianMatrix<scalar_t>& A,
    HermitianMatrix<scalar_t>& B,
    std::vector< blas::real_type<scalar_t> >& Lambda,
    Options const& opts = Options())
{
    Matrix<scalar_t> Z;
    hegv( itype, A, B, Lambda, Z, opts );
}

/// Without Z, compute only eigenvalues. Same as eig_vals.
template <typename scalar_t>
void eig(
    int64_t itype,
    HermitianMatrix<scalar_t>& A,
    HermitianMatrix<scalar_t>& B,
    std::vector< blas::real_type<scalar_t> >& Lambda,
    Options const& opts = Options())
{
    eig_vals( itype, A, B, Lambda, opts );
}

/// With Z, compute eigenvalues & eigenvectors.
template <typename scalar_t>
void eig(
    int64_t itype,
    HermitianMatrix<scalar_t>& A,
    HermitianMatrix<scalar_t>& B,
    std::vector< blas::real_type<scalar_t> >& Lambda,
    Matrix<scalar_t>& Z,
    Options const& opts = Options())
{
    hegv( itype, A, B, Lambda, Z, opts );
}

//-----------------------------------------
// Real-symmetric matrices; disabled for complex
template <typename scalar_t>
void eig_vals(
    int64_t itype,
    SymmetricMatrix<scalar_t>& A,
    SymmetricMatrix<scalar_t>& B,
    std::vector< blas::real_type<scalar_t> >& Lambda,
    Options const& opts = Options(),
    enable_if_t< ! is_complex<scalar_t>::value >* = nullptr)
{
    Matrix<scalar_t> Z;
    sygv( itype, A, B, Lambda, Z, opts );
}

/// Without Z, compute only eigenvalues. Same as eig_vals.
template <typename scalar_t>
void eig(
    int64_t itype,
    SymmetricMatrix<scalar_t>& A,
    SymmetricMatrix<scalar_t>& B,
    std::vector< blas::real_type<scalar_t> >& Lambda,
    Options const& opts = Options(),
    enable_if_t< ! is_complex<scalar_t>::value >* = nullptr)
{
    eig_vals( itype, A, B, Lambda, opts );
}

/// With Z, compute eigenvalues & eigenvectors.
template <typename scalar_t>
void eig(
    int64_t itype,
    SymmetricMatrix<scalar_t>& A,
    SymmetricMatrix<scalar_t>& B,
    std::vector< blas::real_type<scalar_t> >& Lambda,
    Matrix<scalar_t>& Z,
    Options const& opts = Options(),
    enable_if_t< ! is_complex<scalar_t>::value >* = nullptr)
{
    sygv( itype, A, B, Lambda, Z, opts );
}

} // namespace slate

#endif // SLATE_SIMPLIFIED_API_HH
