Linear Systems
==============

SLATE provides comprehensive routines for solving linear systems :math:`AX = B`.

.. contents:: Contents
   :local:
   :depth: 2

General (LU)
------------

.. doxygengroup:: lu_solve
   :project: SLATE
   :content-only:
   :members:

Positive Definite (Cholesky)
-----------------------------

.. doxygengroup:: chol_solve
   :project: SLATE
   :content-only:
   :members:

Symmetric Indefinite
--------------------

.. doxygengroup:: indefinite_solve
   :project: SLATE
   :content-only:
   :members:

Triangular Systems
------------------

.. doxygengroup:: triangular_solve
   :project: SLATE
   :content-only:
   :members:

LU Factorization
----------------

.. doxygenfunction:: slate::lu_factor
   :project: SLATE

.. doxygenfunction:: slate::lu_solve_using_factor
   :project: SLATE

.. doxygenfunction:: slate::lu_inverse_using_factor
   :project: SLATE

.. doxygenfunction:: slate::lu_rcondest_using_factor
   :project: SLATE

Cholesky Factorization
-----------------------

.. doxygenfunction:: slate::chol_factor
   :project: SLATE

.. doxygenfunction:: slate::chol_solve_using_factor
   :project: SLATE

.. doxygenfunction:: slate::chol_inverse_using_factor
   :project: SLATE

.. doxygenfunction:: slate::chol_rcondest_using_factor
   :project: SLATE

Symmetric Indefinite Factorization
-----------------------------------

.. doxygenfunction:: slate::indefinite_factor
   :project: SLATE

.. doxygenfunction:: slate::indefinite_solve_using_factor
   :project: SLATE

BLAS-like Functions (gesv, posv, etc.)
---------------------------------------

See :doc:`blas` for the traditional BLAS/LAPACK-named functions.
