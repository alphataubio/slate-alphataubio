SLATE - Software for Linear Algebra Targeting Exascale
======================================================

**SLATE** is a modern C++ library providing dense linear algebra capabilities for high-performance 
computing systems with multi-core processors and hardware accelerators. SLATE provides coverage of 
existing ScaLAPACK functionality and is designed as a replacement for ScaLAPACK, which cannot be 
adequately retrofitted for modern accelerated architectures.

.. grid:: 2

    .. grid-item-card:: 🚀 Quick Start
        :link: user_guide/getting_started
        :link-type: doc

        Get started with SLATE in minutes. Learn installation, basic usage, and run your first example.

    .. grid-item-card:: 📖 User Guide
        :link: user_guide/index
        :link-type: doc

        Comprehensive guide covering matrices, operations, and all SLATE features.

    .. grid-item-card:: 📚 API Reference
        :link: api/slate/index
        :link-type: doc

        Complete API documentation for all SLATE functions and classes.

    .. grid-item-card:: 💡 Examples
        :link: examples/index
        :link-type: doc

        Standalone examples demonstrating SLATE features and usage.

    .. grid-item-card:: 🧪 Testing & Tuning
        :link: user_guide/testing
        :link-type: doc

        Testing suite, benchmarking, and performance tuning guidance.


Key Features
------------

- **Distributed Computing**: Efficient 2D block-cyclic distribution using MPI
- **GPU Acceleration**: Support for NVIDIA (CUDA), AMD (ROCm), and Intel (SYCL) GPUs
- **Modern C++ API**: Clean, type-safe interface with simplified naming
- **ScaLAPACK Compatible**: Easy transition with compatible data layouts and API
- **Comprehensive Coverage**: Linear systems, least squares, eigenvalues, SVD, and more
- **Mixed Precision**: Iterative refinement with lower precision for performance


Quick Example
-------------

.. code-block:: cpp

    #include <slate/slate.hh>
    
    // Create matrices on 2x2 process grid
    slate::Matrix<double> A(n, n, nb, p, q, MPI_COMM_WORLD);
    slate::Matrix<double> B(n, nrhs, nb, p, q, MPI_COMM_WORLD);
    
    // Allocate and initialize tiles
    A.insertLocalTiles();
    B.insertLocalTiles();
    
    // Solve AX = B using LU factorization
    slate::lu_solve(A, B);


Resources
---------

* **GitHub**: https://github.com/icl-utk-edu/slate/
* **Website**: https://icl.utk.edu/slate/
* **User Forum**: https://groups.google.com/a/icl.utk.edu/g/slate-user


.. toctree::
   :maxdepth: 2
   :caption: USER GUIDE
   :hidden:
   :titlesonly:

   user_guide/index


.. toctree::
   :maxdepth: 2
   :caption: API REFERENCE
   :hidden:
   :titlesonly:

   api/slate/index
   api/blaspp/index
   api/lapackpp/index


.. toctree::
   :maxdepth: 2
   :caption: EXAMPLES
   :hidden:
   :titlesonly:

   examples/index


.. toctree::
   :maxdepth: 2
   :caption: DEVELOPER GUIDE
   :hidden:
   :titlesonly:

   developer_guide/index


.. toctree::
   :maxdepth: 1
   :caption: ADDITIONAL INFO
   :hidden:
   :titlesonly:

   about
   changelog
   license


Indices and Tables
------------------

* :ref:`genindex`
* :ref:`search`


Citation
--------

.. code-block:: bibtex

    @techreport{gates2020slate,
        author={Gates, Mark and Charara, Ali and Kurzak, Jakub and YarKhan, Asim
                and Al Farhan, Mohammed and Sukkari, Dalal and Burgess, Treece
                and Lindquist, Neil and Dongarra, Jack},
        title={{SLATE} Users' Guide, {SWAN} No. 10},
        institution={Innovative Computing Laboratory, University of Tennessee},
        year={2020},
        month={July},
        number={ICL-UT-19-01},
        note={revision 2023-11},
        url={https://www.icl.utk.edu/publications/swan-010},
    }
