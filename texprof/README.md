# The TeX Macro Profiler

## News

- The program `texprof` now has a -pdf option that makes texprof implement
(a large subset of) pdftex primitives. Using this option you can profile
macros that usually are executed only when running pdftex.

- The format files of `texprof` now store file and line information for
all sources used to generate the format file. The profiler can then
point you to the expensive lines in these source files.

- The program `tprof` was renamed to `texprofile`.

## Description
This repository implements two programs: `texprof` and `texprofile`.

`texprof` is a TeX engine, based on Donald Knuths TeX program.
Like other TeX engines, it takes a `.tex` input file and produces
a `.dvi` output file. It can, however, also produce `.tprof`
output files. The `.tprof` files contain a transcript of the actions
of `texprof` and the time it took to execute these actions.
Even a simple `.tex` file requires thousands of actions
to translate it into a `.dvi` and because recording all
these actions should disturb the time measurements as
little as possible, almost no computations are done
during data collection, and the data is written to
the `.tprof` file in a raw, binary format.

`texprofile` is the program to read such a `.tprof` file,
analyze the data, and display it in a reasonable
format.

`texprof` and `texprofile` are written as literate `cweb` programs
`texprof.w` and `texprofile.w.` Using `ctangle` you can generate
normal C programs, `texprof.c` and `texprofile.c`,
from which you can obtain executable programs with a C
compiler. Further, with `cweave` you can generate
`texprof.tex` and `texprofile.tex` from which you can produce
the documentation as PDF files with `pdftex`,
as HINT files with `hitex` or even as DVI files with `texprof`.

In case you do not have the `cweb` system installed, you find
the C and PDF files in the `src/` and `doc/` subdirectories as well.

In case you just want a short instruction manual, you will have to
wait a little.  My talk at the TUG 2024 conference
https://tug.org/tug2024/ is available on youtube (Day 1 stream) and an
updated version will be published in TUGBoat
(https://tug.org/TUGboat/) vol. 45, no. 2.  After that, I will prepare
some more documentation to appear here.

## Installation
For Installation instructions see the `Makefile` in the `src/` subdirectory.


## Directories
doc - for documentation

src - C sources

aux - for auxiliary files

fmt - for format files


## Authors
Martin Ruckert, Hochschule München,

## WWW
`http://hint.userweb.mwn.de/`

## License
All the examples and code you find here is in the public domain unless stated otherwise.

## Project status
Work in progress

