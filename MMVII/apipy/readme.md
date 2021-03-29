pymmv2: MicMacv2 Python API
===========================

Introduction
------------

This is an API to a small part of MicMacv2 for Python 3.

Usage
-----

```python
    import mmv2
    
```

More usage examples can be found in apipy/examples_py

Documentation
-------------
See doc/


Compilation
-----------
Only tested on Linux.

Dependencies:
 - SWIG
 - pkg-config
 - Python 3 headers
 - for documentation: doxygen, GraphViz

On debian:
    apt install swig python3-dev doxygen graphviz pkg-config

    make -f Makefile_apipy_linux


Developement
------------

To add MMv2 classes to python, add then to mmv2.i file (both #include and %include).
If you want to be able to use python lists for objects of these classes, use %template.

This way you can see every undefined references that you have to fix (by adding other files or hiding it with #ifndef SWIG).

PIP package tutorial: https://packaging.python.org/tutorials/packaging-projects/


TODO
----

