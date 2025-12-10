Example 13: Non-uniform Block Sizes
===================================

This example demonstrates creating a matrix with non-uniform tile sizes.

Key Concepts
------------

1.  **Lambda Constructors**: Using lambda functions to define tile properties (`tileNb`, `tileRank`, `tileDevice`) instead of fixed values.
2.  **Custom Block Sizes**: Defining a function that returns the block size for a given block index :math:`j`.
3.  **Process/Device Mapping**: Using helper functions like `slate::func::process_2d_grid` and `slate::func::device_1d_grid` to define distribution.

C++ Example
-----------

.. literalinclude:: ../../../examples/ex13_non_uniform_block_size.cc
   :language: cpp
   :linenos:
