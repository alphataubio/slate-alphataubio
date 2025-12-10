Example 14: ScaLAPACK Compatibility
===================================

This example demonstrates SLATE's ScaLAPACK compatibility layer.

Key Concepts
------------

1.  **ScaLAPACK Interception**: SLATE can intercept standard ScaLAPACK calls (like ``pdgemm``) and execute them using SLATE algorithms.
2.  **Legacy Code Support**: Allows existing ScaLAPACK applications to benefit from SLATE performance without code changes (just linking).
3.  **BLACS Initialization**: The example sets up the BLACS grid and ScaLAPACK descriptors as usual.

C++ Example
-----------

.. literalinclude:: ../../../examples/ex14_scalapack_gemm.cc
   :language: cpp
   :linenos:
