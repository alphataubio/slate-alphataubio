Example 04: Matrix Norms
========================

This example demonstrates how to compute various matrix norms.

Key Concepts
------------

1.  **Norm Types**:
    *   ``Norm::One``: Maximum column sum.
    *   ``Norm::Inf``: Maximum row sum.
    *   ``Norm::Max``: Maximum absolute element.
    *   ``Norm::Fro``: Frobenius norm (square root of sum of squares).
2.  **Polymorphism**: The ``slate::norm`` function works for all matrix types (General, Symmetric, Hermitian, Triangular, Trapezoid).

C++ Example
-----------

.. literalinclude:: ../../../examples/ex04_norm.cc
   :language: cpp
   :linenos:
