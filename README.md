a2GoAT {#mainpage}
======

GoAT == Generation of Analysis Trees

This code is designed to be an analysis package for a tree based analysis 
of a2 data. A correlated ("physics") class exists inside of the A2 AcquRoot
code named TA2GoAT. This class is specifically designed for use with a2GoAT.

The idea: AcquRoot (when used with the TA2GoAT physics class) produces basic track information, but nothing more. Clustering and track reconstruction is completed but any further physics evaluation will be handled by a2GoAT. This includes particle reconstruction, missing masses/energies, etc. 

Basic Code: 
- Tree Managers exist to handle the incoming and outgoing tree files.
- Reconstruction classes will exist to do particle reconstruction, lin pol reconstruction, etc.
- A sorting class will exist to provide reduced data sets for fast physics analysis

Installation
------------

With CMake, it is required to build "outside" of the source
directory (e.g. in an empty subfolder). Thus, we create an extra
`build` sub-directory including all Makefiles (execute in "a2GoAT"
basedir containing folders named cmake, inc, src, ...):

`mkdir build && cd build && cmake ..`

Note that the two dots in the end really mean the parent directory
(where the central CMakeLists.txt is located). Furthermore, it
defaults to Debug mode and tells you exactly where the to-be-built
libraries and binaries are located. You might want to add the binary
path to your PATH environment (but if you use QtCreator, not even that
is required).

Then start the parallel compilation for example on a QuadCore machine as 
(from inside the build directory!)

`make -j5`

