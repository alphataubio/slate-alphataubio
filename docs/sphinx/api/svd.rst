Singular Value Decomposition
=============================

Compute the singular value decomposition :math:`A = U \Sigma V^H`.

.. contents:: Contents
   :local:
   :depth: 2

SVD Functions
-------------

.. doxygenfunction:: slate::svd
   :project: SLATE

.. doxygenfunction:: slate::gesvd
   :project: SLATE

.. doxygenfunction:: slate::gesdd
   :project: SLATE

SVD with Values Only
--------------------

.. doxygenfunction:: slate::svd_vals
   :project: SLATE

Notes
-----

The SVD computes:

.. math::

   A = U \Sigma V^H

where:
- :math:`U` is m-by-m unitary
- :math:`\Sigma` is m-by-n diagonal with non-negative real entries
- :math:`V` is n-by-n unitary
