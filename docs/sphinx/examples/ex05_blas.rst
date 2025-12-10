Example 05: BLAS Operations
===========================

This example demonstrates how to perform Basic Linear Algebra Subprograms (BLAS) operations in SLATE.

Key Concepts
------------

1.  **Matrix Multiplication**: Using ``slate::multiply`` (gemm, hemm, symm) for matrix products.
2.  **Rank Updates**: Performing rank-k (herk, syrk) and rank-2k (her2k, syr2k) updates.
3.  **Triangular Operations**: Triangular matrix multiplication (trmm) and solving triangular systems (trsm).
4.  **Simplified vs Traditional API**: Comparing the descriptive ``multiply`` API with the traditional BLAS-named API.

C++ Example
-----------

.. literalinclude:: ../../../examples/ex05_blas.cc
   :language: cpp
   :linenos:

C API Example
-------------

.. literalinclude:: ../../../examples/c_api/ex05_blas.c
   :language: c
   :linenos:

Fortran API Example
-------------------

.. literalinclude:: ../../../examples/fortran/ex05_blas.f90
   :language: fortran
   :linenos:
