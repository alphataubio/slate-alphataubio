Eigenvalue Problems
===================

LAPACK++ provides comprehensive routines for computing eigenvalues and eigenvectors of various matrix types.

Symmetric/Hermitian Eigenvalue Problems
----------------------------------------

**syev**, **heev** - Compute all eigenvalues/vectors using divide-and-conquer

**syevd**, **heevd** - Faster divide-and-conquer algorithm

**syevx**, **heevx** - Compute selected eigenvalues/vectors by value or index

**syevr**, **heevr** - Compute selected eigenvalues using MRRR algorithm (fastest, most accurate)

**sygv**, **hegv** - Generalized eigenvalue problem :math:`Ax = \lambda Bx`

Tridiagonal Eigenvalue Problems
--------------------------------

**stev** - Compute all eigenvalues/vectors of real symmetric tridiagonal

**stevd** - Faster divide-and-conquer for tridiagonal

**stevx** - Compute selected eigenvalues/vectors of tridiagonal

**stevr** - Use MRRR algorithm for tridiagonal (fastest)

**stebz** - Compute selected eigenvalues using bisection

**stein** - Compute eigenvectors by inverse iteration given eigenvalues

General Nonsymmetric Eigenvalue Problems
-----------------------------------------

**geev** - Compute all eigenvalues and optionally left/right eigenvectors

**geevx** - Expert driver with balancing and condition numbers

**gees** - Compute Schur form with optional eigenvalue ordering

**geesx** - Schur form with condition numbers

**trevc** - Compute eigenvectors from Schur form

Generalized Nonsymmetric Problems
----------------------------------

**ggev** - Generalized eigenvalue problem :math:`Ax = \lambda Bx`

**gges** - Generalized Schur form

Schur Decomposition
-------------------

**hseqr** - Compute Schur form of upper Hessenberg matrix

**trsen** - Reorder Schur factorization

**trexc** - Exchange diagonal blocks in Schur form

**trsyl** - Solve Sylvester equation :math:`AX + XB = C`

Example Usage
-------------

Compute all eigenvalues of symmetric matrix:

.. code-block:: cpp

   int64_t n = 100;
   std::vector<double> A(n * n);  // Symmetric matrix
   std::vector<double> w(n);       // Eigenvalues
   
   // Fill lower triangle of A...
   
   // Compute eigenvalues only
   int64_t info = lapack::syev(lapack::Job::NoVec, 
                                lapack::Uplo::Lower,
                                n, A.data(), n, w.data());
   
   if (info == 0) {
       // Eigenvalues in w, ascending order
   }

Compute eigenvalues and eigenvectors:

.. code-block:: cpp

   int64_t n = 100;
   std::vector<double> A(n * n);
   std::vector<double> w(n);
   
   // Compute both eigenvalues and eigenvectors
   int64_t info = lapack::syev(lapack::Job::Vec,
                                lapack::Uplo::Lower,
                                n, A.data(), n, w.data());
   
   if (info == 0) {
       // Eigenvalues in w
       // Eigenvectors in columns of A
       // A(:,i) is eigenvector for eigenvalue w[i]
   }

Compute selected eigenvalues by value range:

.. code-block:: cpp

   int64_t n = 100;
   std::vector<double> A(n * n);
   std::vector<double> w(n);
   std::vector<double> Z(n * n);  // Eigenvectors
   std::vector<int64_t> ifail(n);
   int64_t nfound;  // Number found
   
   double vl = -1.0, vu = 5.0;  // Value range [vl, vu]
   double abstol = 0.0;          // Tolerance (0 = default)
   
   // Find eigenvalues in range [-1, 5]
   int64_t info = lapack::syevx(
       lapack::Job::Vec,           // Compute vectors
       lapack::Range::Value,       // Select by value
       lapack::Uplo::Lower,
       n, A.data(), n,
       vl, vu,                     // Value range
       0, 0,                       // Index range (unused)
       abstol, &nfound,            // Tolerance, count
       w.data(),                   // Eigenvalues (nfound values)
       Z.data(), n,                // Eigenvectors (n x nfound)
       ifail.data()                // Failed indices
   );
   
   if (info == 0) {
       // Found nfound eigenvalues in [vl, vu]
       // Eigenvalues in w[0:nfound-1]
       // Eigenvectors in Z[:,0:nfound-1]
   }

Compute selected eigenvalues by index range:

.. code-block:: cpp

   int64_t n = 100;
   int64_t il = 1, iu = 10;  // Get smallest 10 eigenvalues (1-indexed)
   int64_t nfound;
   
   std::vector<double> A(n * n);
   std::vector<double> w(n);
   std::vector<double> Z(n * iu);  // Need n x iu storage
   std::vector<int64_t> ifail(n);
   
   int64_t info = lapack::syevx(
       lapack::Job::Vec,
       lapack::Range::Index,       // Select by index
       lapack::Uplo::Lower,
       n, A.data(), n,
       0.0, 0.0,                   // Value range (unused)
       il, iu,                     // Index range [1, 10]
       0.0, &nfound,
       w.data(), Z.data(), n,
       ifail.data()
   );

Generalized eigenvalue problem:

.. code-block:: cpp

   int64_t n = 100, itype = 1;
   std::vector<double> A(n * n);  // General matrix
   std::vector<double> B(n * n);  // SPD matrix
   std::vector<double> w(n);
   
   // Solve A*x = lambda*B*x (itype = 1)
   // Or   A*B*x = lambda*x   (itype = 2)
   // Or   B*A*x = lambda*x   (itype = 3)
   
   int64_t info = lapack::sygv(
       itype,
       lapack::Job::Vec,
       lapack::Uplo::Lower,
       n, A.data(), n, B.data(), n,
       w.data()
   );
   
   if (info == 0) {
       // Generalized eigenvalues in w
       // Eigenvectors in A
   } else if (info > n) {
       // B not positive definite
   }

General nonsymmetric eigenvalues:

.. code-block:: cpp

   int64_t n = 100;
   std::vector<double> A(n * n);
   std::vector<double> wr(n), wi(n);  // Real, imaginary parts
   std::vector<double> VL(n * n), VR(n * n);  // Left, right vectors
   
   int64_t info = lapack::geev(
       lapack::Job::Vec,      // Compute left vectors
       lapack::Job::Vec,      // Compute right vectors
       n, A.data(), n,
       wr.data(), wi.data(),  // Eigenvalues
       VL.data(), n,          // Left eigenvectors
       VR.data(), n           // Right eigenvectors
   );
   
   if (info == 0) {
       // Real eigenvalues: (wr[i], 0)
       // Complex eigenvalues: (wr[i] ± wi[i]*I)
       // If wi[i] > 0: VR[:,i] + I*VR[:,i+1]
       // If wi[i] < 0: VR[:,i] - I*VR[:,i+1]
   }

Schur decomposition with eigenvalue selection:

.. code-block:: cpp

   int64_t n = 100;
   std::vector<double> A(n * n);
   std::vector<double> wr(n), wi(n);
   std::vector<double> VS(n * n);  // Schur vectors
   int64_t sdim;  // Number selected
   
   // Select function: return 1 to select eigenvalue
   auto select = [](const double* wr, const double* wi) -> int {
       return (*wr < 0.0) ? 1 : 0;  // Select negative real part
   };
   
   int64_t info = lapack::gees(
       lapack::Job::Vec,         // Compute Schur vectors
       lapack::Sort::Sorted,     // Sort eigenvalues
       select,                   // Selection function
       n, A.data(), n,
       &sdim,                    // Number selected
       wr.data(), wi.data(),
       VS.data(), n
   );
   
   if (info == 0) {
       // A = VS * T * VS^T where T is quasi-upper triangular
       // sdim eigenvalues with select(wr, wi) = 1
   }

Performance Comparison
----------------------

For symmetric/Hermitian matrices (n = 1000):

- **syevr/heevr**: Fastest, most accurate (MRRR algorithm)
- **syevd/heevd**: ~2-3x faster than syev/heev (divide-and-conquer)
- **syev/heev**: Stable QR algorithm (slower)
- **syevx/heevx**: Efficient for selected eigenvalues only

For general matrices:

- **geev**: Standard QR algorithm, O(n³)
- **geevx**: Additional balancing and condition estimates
- **gees**: Schur form, useful for reordering

Tips for Best Performance
--------------------------

1. **Use ∗evr for symmetric**: heevr/syevr is fastest and most accurate
2. **Compute only what you need**: NoVec is faster if eigenvectors not needed
3. **Use ∗evx for subsets**: Much faster when only some eigenvalues needed
4. **Consider divide-and-conquer**: ∗evd is fast for all eigenvalues
5. **Balance general matrices**: geevx balancing improves conditioning

Accuracy Considerations
------------------------

- Symmetric/Hermitian: Always backward stable, eigenvalues accurate to machine precision
- General matrices: Sensitive to ill-conditioning, use geevx for condition estimates
- MRRR algorithm (∗evr): More accurate than QR for clustered eigenvalues
- Generalized problems: Accuracy depends on condition of B

See Also
--------

- :doc:`factorizations` - QR, Hessenberg reduction used internally
- :doc:`auxiliary` - Balancing, scaling routines
