BLAS and Auxiliary Operations
=============================

SLATE provides parallel distributed implementations of BLAS operations and auxiliary routines.


Matrix Multiply (gemm)
----------------------

General matrix-matrix multiplication.

.. cpp:function:: template <typename scalar_t> \
                  void multiply(scalar_t alpha, Matrix<scalar_t>& A, Matrix<scalar_t>& B, \
                               scalar_t beta, Matrix<scalar_t>& C, Options const& opts = {})

.. cpp:function:: template <typename scalar_t> \
                  void gemm(scalar_t alpha, Matrix<scalar_t>& A, Matrix<scalar_t>& B, \
                           scalar_t beta, Matrix<scalar_t>& C, Options const& opts = {})

Computes :math:`C = \alpha \text{op}(A) \text{op}(B) + \beta C`

Parameters:
    - **alpha** -- Scalar multiplier for A*B
    - **A** -- Input matrix (or transposed/conjugate-transposed view)
    - **B** -- Input matrix (or transposed/conjugate-transposed view)
    - **beta** -- Scalar multiplier for C
    - **C** -- Input/output matrix
    - **opts** -- Execution options

Example:

.. code-block:: cpp

    slate::multiply(alpha, A, B, beta, C);
    
    // With transposed matrices
    auto AT = slate::transpose(A);
    auto BH = slate::conj_transpose(B);
    slate::multiply(alpha, AT, BH, beta, C);

Options:
    - ``Target``: Execution target
    - ``Lookahead``: Lookahead depth
    - ``MethodGemm``: Algorithm variant (Auto, GemmA, GemmC)


Hermitian/Symmetric Matrix Multiply (hemm/symm)
-----------------------------------------------

Matrix multiply where one operand is Hermitian or symmetric.

.. cpp:function:: template <typename scalar_t> \
                  void multiply(scalar_t alpha, HermitianMatrix<scalar_t>& A, Matrix<scalar_t>& B, \
                               scalar_t beta, Matrix<scalar_t>& C, Options const& opts = {})

.. cpp:function:: template <typename scalar_t> \
                  void hemm(Side side, scalar_t alpha, HermitianMatrix<scalar_t>& A, \
                           Matrix<scalar_t>& B, scalar_t beta, Matrix<scalar_t>& C, \
                           Options const& opts = {})

For ``Side::Left``: :math:`C = \alpha A B + \beta C` where A is Hermitian

For ``Side::Right``: :math:`C = \alpha B A + \beta C` where A is Hermitian

Parameters:
    - **side** -- Left or Right multiplication
    - **alpha, beta** -- Scalar multipliers
    - **A** -- Hermitian/symmetric matrix
    - **B** -- General matrix
    - **C** -- Output matrix

Example:

.. code-block:: cpp

    // A on left (simplified API)
    slate::multiply(alpha, A_hermitian, B, beta, C);
    
    // A on right (note order in simplified API)
    slate::multiply(alpha, B, A_hermitian, beta, C);
    
    // Traditional API
    slate::hemm(slate::Side::Left, alpha, A_hermitian, B, beta, C);

The ``symm`` function works identically for symmetric matrices.


Rank-k Update (herk/syrk)
-------------------------

Hermitian or symmetric rank-k update.

.. cpp:function:: template <typename scalar_t> \
                  void rank_k_update(blas::real_type<scalar_t> alpha, Matrix<scalar_t>& A, \
                                    blas::real_type<scalar_t> beta, HermitianMatrix<scalar_t>& C, \
                                    Options const& opts = {})

.. cpp:function:: template <typename scalar_t> \
                  void herk(blas::real_type<scalar_t> alpha, Matrix<scalar_t>& A, \
                           blas::real_type<scalar_t> beta, HermitianMatrix<scalar_t>& C, \
                           Options const& opts = {})

Computes :math:`C = \alpha A A^H + \beta C` where C is Hermitian.

Example:

.. code-block:: cpp

    // Hermitian rank-k update
    slate::rank_k_update(alpha, A, beta, C_hermitian);
    slate::herk(alpha, A, beta, C_hermitian);
    
    // Symmetric rank-k update: C = alpha * A * A^T + beta * C
    slate::rank_k_update(alpha, A, beta, C_symmetric);
    slate::syrk(alpha, A, beta, C_symmetric);


Rank-2k Update (her2k/syr2k)
----------------------------

Hermitian or symmetric rank-2k update.

.. cpp:function:: template <typename scalar_t> \
                  void rank_2k_update(scalar_t alpha, Matrix<scalar_t>& A, Matrix<scalar_t>& B, \
                                     blas::real_type<scalar_t> beta, HermitianMatrix<scalar_t>& C, \
                                     Options const& opts = {})

Computes :math:`C = \alpha A B^H + \bar{\alpha} B A^H + \beta C` where C is Hermitian.

Example:

.. code-block:: cpp

    slate::rank_2k_update(alpha, A, B, beta, C_hermitian);
    slate::her2k(alpha, A, B, beta, C_hermitian);


Triangular Matrix Multiply (trmm)
---------------------------------

Multiply by triangular matrix.

.. cpp:function:: template <typename scalar_t> \
                  void triangular_multiply(scalar_t alpha, TriangularMatrix<scalar_t>& A, \
                                          Matrix<scalar_t>& B, Options const& opts = {})

For ``Side::Left``: :math:`B = \alpha A B`

For ``Side::Right``: :math:`B = \alpha B A`

Example:

.. code-block:: cpp

    // A on left
    slate::triangular_multiply(alpha, A_triangular, B);
    slate::trmm(slate::Side::Left, alpha, A_triangular, B);
    
    // A on right (note order in simplified API)
    slate::triangular_multiply(alpha, B, A_triangular);
    slate::trmm(slate::Side::Right, alpha, A_triangular, B);


Triangular Solve (trsm)
-----------------------

Solve triangular system with multiple right-hand sides.

.. cpp:function:: template <typename scalar_t> \
                  void triangular_solve(scalar_t alpha, TriangularMatrix<scalar_t>& A, \
                                       Matrix<scalar_t>& B, Options const& opts = {})

For ``Side::Left``: Solve :math:`A X = \alpha B`, result in B

For ``Side::Right``: Solve :math:`X A = \alpha B`, result in B

Example:

.. code-block:: cpp

    // Solve A * X = alpha * B
    slate::triangular_solve(alpha, A_triangular, B);
    slate::trsm(slate::Side::Left, alpha, A_triangular, B);
    
    // Solve X * A = alpha * B
    slate::triangular_solve(alpha, B, A_triangular);
    slate::trsm(slate::Side::Right, alpha, A_triangular, B);


Matrix Norms
------------

Compute matrix norms.

.. cpp:function:: template <typename matrix_type> \
                  blas::real_type<typename matrix_type::value_type> \
                  norm(Norm norm_type, matrix_type& A, Options const& opts = {})

Parameters:
    - **norm_type** -- Type of norm:
        - ``Norm::One``: Maximum column sum
        - ``Norm::Inf``: Maximum row sum  
        - ``Norm::Fro``: Frobenius norm
        - ``Norm::Max``: Maximum absolute element
    - **A** -- Input matrix (any matrix type)

Example:

.. code-block:: cpp

    double norm_1   = slate::norm(slate::Norm::One, A);
    double norm_inf = slate::norm(slate::Norm::Inf, A);
    double norm_fro = slate::norm(slate::Norm::Fro, A);
    double norm_max = slate::norm(slate::Norm::Max, A);


Matrix Add
----------

Add two matrices.

.. cpp:function:: template <typename scalar_t> \
                  void add(scalar_t alpha, Matrix<scalar_t>& A, \
                          scalar_t beta, Matrix<scalar_t>& B, Options const& opts = {})

Computes :math:`B = \alpha A + \beta B`

Example:

.. code-block:: cpp

    slate::add(alpha, A, beta, B);


Matrix Copy
-----------

Copy matrix, optionally with precision conversion.

.. cpp:function:: template <typename src_scalar_t, typename dst_scalar_t> \
                  void copy(Matrix<src_scalar_t>& A, Matrix<dst_scalar_t>& B, \
                           Options const& opts = {})

Example:

.. code-block:: cpp

    // Same precision
    slate::copy(A, B);
    
    // Precision conversion
    slate::Matrix<double> A_double(...);
    slate::Matrix<float> A_float(...);
    slate::copy(A_double, A_float);  // double -> float


Matrix Scale
------------

Scale matrix by scalar.

.. cpp:function:: template <typename scalar_t> \
                  void scale(blas::real_type<scalar_t> alpha, Matrix<scalar_t>& A, \
                            Options const& opts = {})

Computes :math:`A = \alpha A`

Example:

.. code-block:: cpp

    slate::scale(alpha, A);


Row and Column Scaling
~~~~~~~~~~~~~~~~~~~~~~

.. cpp:function:: template <typename scalar_t> \
                  void scale_row_col(Equed equed, std::vector<real_t>& R, \
                                    std::vector<real_t>& C, Matrix<scalar_t>& A, \
                                    Options const& opts = {})

Computes :math:`A = \text{diag}(R) \cdot A \cdot \text{diag}(C)`


Matrix Set
----------

Set matrix elements.

.. cpp:function:: template <typename scalar_t> \
                  void set(scalar_t alpha, scalar_t beta, Matrix<scalar_t>& A, \
                          Options const& opts = {})

Sets off-diagonal elements to alpha, diagonal to beta.

Example:

.. code-block:: cpp

    // Set to identity
    slate::set(0.0, 1.0, A);
    
    // Set all to zero
    slate::set(0.0, 0.0, A);


Band Matrix Operations
----------------------

SLATE supports band matrices with separate bandwidth parameters.

General Band Multiply (gbmm)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. cpp:function:: template <typename scalar_t> \
                  void gbmm(scalar_t alpha, BandMatrix<scalar_t>& A, Matrix<scalar_t>& B, \
                           scalar_t beta, Matrix<scalar_t>& C, Options const& opts = {})

Triangular Band Solve (tbsm)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. cpp:function:: template <typename scalar_t> \
                  void tbsm(Side side, scalar_t alpha, TriangularBandMatrix<scalar_t>& A, \
                           Matrix<scalar_t>& B, Options const& opts = {})


Matrix Print
------------

Print matrix for debugging.

.. cpp:function:: template <typename matrix_type> \
                  void print(const char* label, matrix_type& A, Options const& opts = {})

Options:
    - ``PrintWidth``: Minimum character width per value
    - ``PrintPrecision``: Digits after decimal point
    - ``PrintVerbose``: Verbosity level (0-4)

Example:

.. code-block:: cpp

    slate::Options opts = {
        {slate::Option::PrintVerbose, 2},  // Print corners
    };
    slate::print("A", A, opts);
