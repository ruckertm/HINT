# Binaries for WIN32

## Description
The binaries you find here are the most recent binaries available.
The stable version and sources can be found on the HintView home page:
http://hint.userweb.mwn.de/hint/hintview.html 
 

## Installation

### hitex
The hitex executable uses the kpathsearch library. This library is used
to find and open files. For this job, it must be installed in the 
correct directory. So you need an instalation of TeX Live 2022 or newer
and install hitex in the same directory where the other executables
of TeX Live are installed. On my machine, binaries of TeX Live
are installed in /usr/local/texlive/2022/bin/x86_64-linux/
and this is the directory where hitex must be installed as well.
You can find your binary directory by running "which tex".

### hilatex
There is no separate binary for LaTeX. hilatex is just a link to hitex.
Running hitex under the name hilatex will cause hitex to load a different
format file (see the ../format directory).

### hintview
Just download and move the executable to a place on your path.
This is a dynamically linked ELF 64-bit LSB executable for Linux x86-64.
It needs these shared librarys: 
libglfw.so.3
libGLEW.so.1.13
libdl.so.2
libfreetype.so.6
libX11.so.6
libXrandr.so.2
libXinerama.so.1
libXi.so.6
libXcursor.so.1
libGL.so.1
libz.so.1
libpthread.so.0
libm.so.6
libc.so.6

### hintview.1
This is the Linux manual page for hintview. 

It explains how to modify the behaviour of the viewer 
using command line options
and how to use keystrokes and mouse movements.

## Authors
Martin Ruckert, Hochschule München,

## WWW
http://hint.userweb.mwn.de/

## License
All the executables and the code you find here is in the public domain unless stated otherwise. There is no implied warranty for any function not even against
malfunctioning. These are beta test versions.

