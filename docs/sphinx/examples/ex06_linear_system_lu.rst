Example 06: Linear Systems (LU)
===============================

This example demonstrates solving linear systems :math:`Ax=B` using LU factorization.

Key Concepts
------------

1.  **Simple Solve**: Using ``slate::lu_solve`` (gesv) for a one-step solution.
2.  **Explicit Factorization**: Separating factorization (``lu_factor``/``getrf``) and solve (``lu_solve_using_factor``/``getrs``).
3.  **Matrix Inversion**: Computing :math:`A^{-1}` using ``lu_inverse_using_factor`` (getri).
4.  **Mixed Precision**: Using iterative refinement to solve systems with lower-precision factorization.
5.  **Condition Number**: Estimating the condition number of the matrix.

C++ Example
-----------

.. literalinclude:: ../../../examples/ex06_linear_system_lu.cc
   :language: cpp
   :linenos:

C API Example
-------------

.. literalinclude:: ../../../examples/c_api/ex06_linear_system_lu.c
   :language: c
   :linenos:
