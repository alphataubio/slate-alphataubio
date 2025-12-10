Examples
========

These are designed as minimal, standalone examples to demonstrate how to include, call, and link with SLATE.

These examples are used in the `SLATE tutorial presentation <https://bitbucket.org/icl/slate/downloads/2023-02-ecp-slate-tutorial.pdf>`_.

.. toctree::
   :maxdepth: 1
   :caption: Example List

   ex01_matrix
   ex02_conversion
   ex03_submatrix
   ex04_norm
   ex05_blas
   ex06_linear_system_lu
   ex07_linear_system_cholesky
   ex08_linear_system_indefinite
   ex09_least_squares
   ex10_svd
   ex11_hermitian_eig
   ex12_generalized_hermitian_eig
   ex13_non_uniform_block_size
   ex14_scalapack_gemm
   ex15_set_matrix

Building Examples
-----------------

For compiling, there are two options:

Option 1: Makefile
^^^^^^^^^^^^^^^^^^

Build & install SLATE (see INSTALL.md). This installs it into a sub-directory of the SLATE source.

.. code-block:: bash

    slate>  make
    slate>  make install prefix=install
    slate>  export PKG_CONFIG_PATH=${PKG_CONFIG_PATH}:`pwd`/install/lib/pkgconfig

Build examples:

.. code-block:: bash

    slate>  cd examples
    slate/examples>  make
    slate/examples>  make check

Installation puts the SLATE, BLAS++, and LAPACK++ headers all in the same include directory, and libraries all in the same lib directory, which simplifies compiling the examples. The Makefile queries pkg-config for all settings.

Option 2: CMake
^^^^^^^^^^^^^^^

Build & install SLATE (see INSTALL.md). This installs it into a sub-directory of the SLATE source.

.. code-block:: bash

    slate>  mkdir build && cd build
    slate/build>  cmake -DCMAKE_INSTALL_PREFIX=../install ..
    slate/build>  make
    slate/build>  make install

Build examples:

.. code-block:: bash

    slate/build>  cd ../examples
    slate/examples>  mkdir build && cd build
    slate/examples/build>  cmake -DCMAKE_PREFIX_PATH=`pwd`/../../install ..
    slate/examples/build>  make
    slate/examples/build>  make test

CTest output is in `Testing/Temporary/LastTest.log`.

CMake needs to find the SLATE, BLAS++, and LAPACK++ installations by setting the `CMAKE_PREFIX_PATH` to the absolute path to the install directory.
