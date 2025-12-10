Example 08: Linear Systems (Indefinite)
=======================================

This example demonstrates solving symmetric/Hermitian indefinite linear systems using Aasen's algorithm.

Key Concepts
------------

1.  **Indefinite Solve**: Using ``slate::indefinite_solve`` (hesv/sysv) for symmetric/Hermitian matrices that are not necessarily positive definite.
2.  **Aasen's Algorithm**: A factorization method :math:`A = L T L^H` where :math:`T` is tridiagonal.
3.  **Explicit Factorization**: Using ``indefinite_factor`` (hetrf) and ``indefinite_solve_using_factor`` (hetrs).
4.  **Workspace**: Allocating necessary workspace matrices (BandMatrix T, Matrix H).

C++ Example
-----------

.. literalinclude:: ../../../examples/ex08_linear_system_indefinite.cc
   :language: cpp
   :linenos:
