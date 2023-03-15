# HiLaTeX

## Description
This repository is dedicated to the mutal support of LaTeX and hitex.

## Installation
hitex became a part of the TeX Live distribution in 2022.  The initial
distribution did provide the hilatex executable as a link to the hitex
executable as usual, but the generation of the hilatex format file was
still disabled because there were some LaTeX requirement not yet met
by the hitex executable.

This resository is dedicated to resolving not only issues concerning
the basic requirements for running LaTeX using hilatex, but also
strives to support advanced features of LaTeX like the definition of
links and bookmarks or the embedding of graphics.
Therfore the following directories provide updated files that will 
ultimately be part of the TeX Live development sources and then
move to the TeX Live distribution. The HINT file viewers are an
exception: the production versions of the executables are distributed 
through the various App Stores or on the HintView home page:
http://hint.userweb.mwn.de/hint/hintview.html 

## Directories
doc - for documentation

examples - for examples used as test cases

base - for supplemental tex files that should go to the TeX Live
distribution in directory texlive/20XX/texmf-dist/tex/hitex/base/

win32 - for WIN32 executables

linux - for linux binaries

format - for format files

## Roadmap
The repository will target first the hyperref package of LaTeX with
the aim of supporting first internal links and later
bookmarks. Currently the HINT file format does not have support for
external links.


## Authors
Martin Ruckert, Hochschule München,

## WWW
http://hint.userweb.mwn.de/

## License
All the examples and code you find here is in the public domain unless stated otherwise.

## Project status
Initial setup.

