Example 02: Matrix Type Conversion
==================================

This example demonstrates how to create different matrix views (Trapezoid, Triangular, Symmetric, Hermitian) from a general Matrix.

Key Concepts
------------

1.  **Shallow Copies**: Creating views of existing data without copying the elements.
2.  **Matrix Types**:
    *   ``TrapezoidMatrix``: Lower or Upper trapezoid.
    *   ``TriangularMatrix``: Square lower or upper triangle.
    *   ``SymmetricMatrix``: Symmetric matrix (where :math:`A_{ji} = A_{ij}`).
    *   ``HermitianMatrix``: Hermitian matrix (where :math:`A_{ji} = \bar{A}_{ij}`).
3.  **Slicing**: Creating a square slice of a general matrix to fit triangular requirements.

C++ Example
-----------

.. literalinclude:: ../../../examples/ex02_conversion.cc
   :language: cpp
   :linenos:
