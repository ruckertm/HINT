# The TeX Macro Profiler

## Description
This repository implements two programs: texprof and tprof.

texprof is a TeX engine, based on Donald Knuths TeX program.
Like other TeX engines, it takes a .tex input file and produces
a .dvi output file. It can, however, also produce .tprof
output files. The .tprof files contain a transcript of the actions
of texprof and the time it took to execute these actions.
Even a simple .tex file requires thousands of actions
to translate it into a .dvi and because recording all
these actions should disturb the time measurements as
little as possible, almost no computations are done
during data collection, and the data is written to
the .tprof file in a raw, binary format.

tprof is the program to read such a .tprof file,
analyze the data, and display it in a reasonable
format.

texprof and tprof are written as literate cweb programs
texprof.w and tprof.w. Using ctangle you can generate
normal C programs, texprof.c and tprof.c,
from which you can obtain executable programs with a C
compiler. Further, with cweave you can generate
texprof.tex and tprof.tex from which you can produce
the documentation as PDF files with pdftex, 
as HINT files with hitex or even as DVI files with texprof.

In case you do not have the cweb system installed, you find
the C and PDF files in the src and doc subdirectories as well.

In case you just want a short instruction manual,
you will have to wait a little.
I will give a talk at the TUG 2024
conference and after that, I will prepare some
more documentation to appear here.

## Installation
For Installation instructions see the Makefile in the src subdirectory.


## Directories
doc - for documentation

src - C sources

aux - for auxiliary files 


## Authors
Martin Ruckert, Hochschule München,

## WWW
http://hint.userweb.mwn.de/

## License
All the examples and code you find here is in the public domain unless stated otherwise.

## Project status


