Example 03: Submatrices and Slicing
===================================

This example demonstrates how to work with submatrices in SLATE.

Key Concepts
------------

1.  **Tile Indexing (sub)**: Creating a submatrix view using tile indices (block coordinates). This is the most efficient way to reference submatrices in SLATE.
2.  **Element Indexing (slice)**: Creating a submatrix view using global element indices (row/column coordinates). Note that slices must align with block boundaries if they are to be treated as standard distributed matrices in many operations.

C++ Example
-----------

.. literalinclude:: ../../../examples/ex03_submatrix.cc
   :language: cpp
   :linenos:
