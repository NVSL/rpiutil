This toolchain uses swig library to convert Arduino programs to python. The arduPi library is used to provide Arduino like software bindings. 

Once we build the tool using make:

1. we will get lib/ folder that contains the compiled dynamic libraries and python files
2. we also get include/ folder that has the necessary header files

To add a library or module

1. create a folder for the library
2. create swig interface file for the library in it`s folder
3. create the library`s individual Makefile (use existing one as reference)
4. edit the common Makefile accordingly

Other info:

1. ensure that ARDUPI_HOME variable is set accordingly
2. python shell can be tested by starting in the lib folder like given below

in lib/

sudo LD_LIBRARY_PATH=. python

This ensures that linker looks at the compiled libraries in the lib/ folder
