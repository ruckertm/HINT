## HINT
Sources and Documentation for Viewing HINT files under Linux.

This implementation of a viewing application is the simples of all
the viewing applications presented on this site. It can be used
as a starting point for your own application.

### Makefile
Controls the making of the hintview application.

In addition to the files in this directory, the files in the ../backend
directory are required. 

Further, the following libraries mus be available:
libdl, libglew, libglfw3 libfreetype, libX11, libXrandr, libXinerama, 
libXi, libXcursor, libGL, libz, libpthread, libm, libc.

Depending on the availability of gtk+ it will add a dialog for opening files.
Without gtk+, the input file must be given on the command line.

### hintview.1
The man page for hintview

### main.c and main.h
A short main program

### renderOGL.c
The rendering frontend using OpenGL.
