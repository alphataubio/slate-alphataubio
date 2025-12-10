Example 11: Hermitian Eigenvalue Problems
=========================================

This example demonstrates computing eigenvalues and eigenvectors for Hermitian (or symmetric) matrices.

Key Concepts
------------

1.  **Eigenvalues Only**: Computing just the eigenvalues :math:`\lambda` using ``eig_vals`` (heev).
2.  **Eigenvectors**: Computing eigenvalues and eigenvectors :math:`Z` such that :math:`A Z = Z \Lambda`.
3.  **Simplified vs Traditional**: Using ``slate::eig`` vs ``slate::heev``.

C++ Example
-----------

.. literalinclude:: ../../../examples/ex11_hermitian_eig.cc
   :language: cpp
   :linenos:
