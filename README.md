Calypsi board support for C256 Foenix
=====================================

This project contains a library and linker control files to make
it easy to get started on using the
[Calypsi C compiler](https://www.calypsi.cc/) for the C256 Foenix.

Usage
-----

This project is incorporated in the Calypsi product which comes with
pre-built libraries, header files and linker control files.
To enable it, specify `--target=foenix` on the command line.

You are welcome to help with this project by forking it and adding to
it. When using such variant, you need to specify the path to update
linker files using the `-I` command line option. Changed or added
source files are easiest to include by including the for the time
being in your own project where it is used.

Startup module
--------------

This project contains a startup module for C256 Foenix that is
suitable for starting an application in its kernel environment.

Stub interface
--------------

There is currently very limited stub functionality implemented in this
project. Basically only write to console and handle `exit()`. Feel
free to expand on it.

Notes on stack
--------------

The linker control files have been defined not to set up a stack and
relies on that the stack is already set up by the operating system (or
language environment) which load and run the application.

Alternative use
---------------

If you want more control, e.g. take over the machine completely then
you should probably take a look at the corresponding startup file and
example linker files provided in the Calypsi C compiler package.
