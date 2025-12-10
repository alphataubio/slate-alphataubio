Example 15: Setting Matrix Elements
===================================

This example demonstrates advanced ways to set matrix elements using lambda functions.

Key Concepts
------------

1.  **Functional Initialization**: Using `slate::set` with a lambda function `f(i, j)` to set :math:`A_{ij}`.
2.  **Parallel Execution**: The lambda function is executed in parallel across tiles.
3.  **Use Cases**:
    *   Random initialization (non-deterministic if not careful with seeds).
    *   Coordinate-based initialization (e.g., :math:`A_{ij} = i + j`).
    *   Stencil generation (e.g., Laplacian).

C++ Example
-----------

.. literalinclude:: ../../../examples/ex15_set_matrix.cc
   :language: cpp
   :linenos:
