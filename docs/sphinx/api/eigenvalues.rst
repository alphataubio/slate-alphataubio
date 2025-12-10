Eigenvalue Problems
===================

Compute eigenvalues and eigenvectors of symmetric/Hermitian matrices.

.. contents:: Contents
   :local:
   :depth: 2

Standard Eigenvalue Problems
-----------------------------

Solve :math:`A v = \lambda v` where A is symmetric (real) or Hermitian (complex).

.. doxygenfunction:: slate::eig_vals(HermitianMatrix<scalar_t>&, std::vector<blas::real_type<scalar_t>>&, Options const&)
   :project: SLATE

.. doxygenfunction:: slate::eig(HermitianMatrix<scalar_t>&, std::vector<blas::real_type<scalar_t>>&, Options const&)
   :project: SLATE

.. doxygenfunction:: slate::eig(HermitianMatrix<scalar_t>&, std::vector<blas::real_type<scalar_t>>&, Matrix<scalar_t>&, Options const&)
   :project: SLATE

.. doxygenfunction:: slate::heev
   :project: SLATE

.. doxygenfunction:: slate::syev
   :project: SLATE

Generalized Eigenvalue Problems
--------------------------------

Solve :math:`A v = \lambda B v` where A and B are symmetric/Hermitian.

.. doxygenfunction:: slate::eig_vals(int64_t, HermitianMatrix<scalar_t>&, HermitianMatrix<scalar_t>&, std::vector<blas::real_type<scalar_t>>&, Options const&)
   :project: SLATE

.. doxygenfunction:: slate::eig(int64_t, HermitianMatrix<scalar_t>&, HermitianMatrix<scalar_t>&, std::vector<blas::real_type<scalar_t>>&, Options const&)
   :project: SLATE

.. doxygenfunction:: slate::eig(int64_t, HermitianMatrix<scalar_t>&, HermitianMatrix<scalar_t>&, std::vector<blas::real_type<scalar_t>>&, Matrix<scalar_t>&, Options const&)
   :project: SLATE

.. doxygenfunction:: slate::hegv
   :project: SLATE

.. doxygenfunction:: slate::sygv
   :project: SLATE
