Example 07: Linear Systems (Cholesky)
=====================================

This example demonstrates solving symmetric/Hermitian positive definite linear systems using Cholesky factorization.

Key Concepts
------------

1.  **Cholesky Solve**: Using ``slate::chol_solve`` (posv) for a one-step solution of :math:`AX=B` where :math:`A` is positive definite.
2.  **Explicit Factorization**: Separating factorization (``chol_factor``/``potrf``) and solve (``chol_solve_using_factor``/``potrs``).
3.  **Matrix Inversion**: Computing :math:`A^{-1}` using ``chol_inverse_using_factor`` (potri).
4.  **Mixed Precision**: Using iterative refinement (``posv_mixed``).
5.  **Condition Number**: Estimating the condition number of a Hermitian positive definite matrix.

C++ Example
-----------

.. literalinclude:: ../../../examples/ex07_linear_system_cholesky.cc
   :language: cpp
   :linenos:
