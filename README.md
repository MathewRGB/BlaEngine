# BlaEngine

Chess engine to improve someone, somehow.


## Manual Build

### Linux

This project uses CMake as its build engine. Follow the steps to build the system manually.

Create a temporary build directory:

    $ mkdir build && cd build

Invoke CMake for debugging without compiler flags

    $ cmake ..

Invoke CMake for debugging with compiler flags

    $ cmake -DCMAKE_BUILD_TYPE=Debug ..

Invoke CMake for the release with compiler flags for optimisation

    $ cmake -DCMAKE_BUILD_TYPE=Release ..

Note: at this point you might get CMake errors about various missing packages. Everytime such an error is encountered, install the missing package using your operating system's package manager, then repeat step 3. For example:

Then build the project (for the release)

    $ make

Or build the project with additional informations (for debugging)

    $ make VERBOSE=1

Then run unit tests

    $ ./runTests

For running live tests

    $ ./runTests --gtest_also_run_disabled_tests

To help just type

    $ ./runTests --help

If you like to generate the doxygen documentation inside the build folder just type

    $ make doc

The website will be created into the docs folder. In the docs folder there is also a readme.md that
describes how to build the doxygen documentation manually.
