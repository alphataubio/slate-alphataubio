Example 12: Generalized Hermitian Eigenvalues
=============================================

This example demonstrates solving generalized Hermitian eigenvalue problems.

Key Concepts
------------

1.  **Problem Types**:
    *   Type 1: :math:`Ax = \lambda Bx`
    *   Type 2: :math:`ABx = \lambda x`
    *   Type 3: :math:`BAx = \lambda x`
2.  **Positive Definite B**: The matrix B must be Hermitian positive definite.
3.  **API Usage**: Using ``slate::eig_vals``, ``slate::eig``, and ``slate::hegv`` with the type parameter.

C++ Example
-----------

.. literalinclude:: ../../../examples/ex12_generalized_hermitian_eig.cc
   :language: cpp
   :linenos:
