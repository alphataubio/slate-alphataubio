Example 10: Singular Value Decomposition (SVD)
==============================================

This example demonstrates computing the SVD of a matrix :math:`A = U \Sigma V^H`.

Key Concepts
------------

1.  **Singular Values Only**: Computing just :math:`\Sigma` using ``svd_vals``.
2.  **Full SVD**: Computing :math:`\Sigma`, :math:`U`, and :math:`V^H` using ``svd`` (gesvd).
3.  **Partial Vectors**: Computing only :math:`U` or only :math:`V^H`.

C++ Example
-----------

.. literalinclude:: ../../../examples/ex10_svd.cc
   :language: cpp
   :linenos:
