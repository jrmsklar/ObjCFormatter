## Objective-C Formatter

***C++ based Objective-C formatter. Cleans up Objective-C code, making it easier to work on.***

Overview
------------

Objective-C Formatter is a C++ program used to format Objective-C files.

Formatting Options:

1. Put all function declarations in a `.m` file into the private `@interface` of a .m file.
2. More to come in the future.


Instructions
------------
The program resides in `format.cpp`. Begin by compiling `format.cpp`. Do this by using the Makefile, or typing `make` onto the command line.

The Makefile generates an executable titled `format`. `format` takes either 1 or 2 extra arguments on the command line. The first argument that it takes is required, and is the full path of the input file to be formatted. This must be a `.m` file, and (in `format.cpp`'s current state, it must have a private `@interface`). The second argument is optional, and is the full path for the ouput file. If this argument is not specified, `format` will overwrite the input file. If this argument is specified, it will write to this file.

Future
-------

In the future, I plan on creating an ouput file showing the diff of the input file and the result.

I also plan on creating a lot more formatting options.

