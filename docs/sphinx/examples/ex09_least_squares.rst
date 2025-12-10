Example 09: Least Squares
=========================

This example demonstrates solving overdetermined (:math:`m > n`) and underdetermined (:math:`m < n`) linear systems using least squares.

Key Concepts
------------

1.  **Overdetermined Systems**: Finding :math:`x` that minimizes :math:`\|Ax - B\|_2`.
2.  **Underdetermined Systems**: Finding the minimum norm solution :math:`x` that satisfies :math:`Ax = B`.
3.  **Simplified API**: Using ``slate::least_squares_solve`` which handles both cases automatically.
4.  **Traditional API**: Using ``slate::gels``.

C++ Example
-----------

.. literalinclude:: ../../../examples/ex09_least_squares.cc
   :language: cpp
   :linenos:
