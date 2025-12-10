Example 01: Matrix Construction
===============================

This example demonstrates the fundamental operations for creating and managing SLATE matrices.

Key Concepts
------------

1.  **Constructors**: Creating empty matrices with specific dimensions and distribution.
2.  **Tile Insertion**: Allocating memory for tiles on Host (CPU) or Devices (GPU).
3.  **User Data**: Wrapping existing data pointers (e.g., from ScaLAPACK) into a SLATE matrix.
4.  **Transposition**: Creating transposed views of matrices without copying data.
5.  **Element Access**: Iterating over tiles and elements efficiently.

C++ Example
-----------

.. literalinclude:: ../../../examples/ex01_matrix.cc
   :language: cpp
   :linenos:
