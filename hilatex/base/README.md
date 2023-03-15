# TeX input files

## Description
In not otherwise noted in the files, the files in this directory are 
updated copies of the files from the TeX Live distribution (2022 or later)
from the texmf-dist/tex/hitex/base/ subdirectory of TeX Live.

ifhint.tex - file defining \ifhint to test for the hitex engine

hitex.ini - driver file to generate the plain hitex format

hilatex.ini  - driver file to generate the LaTeX format for hilatex.

hiplainpage.tex - defining a page template to be used with plain hitex

hiltxpage.tex - defining a page template to be used with hilatex

hhitex.def - A preliminary driver file for the hyperref package.
This is an incomplete draft that will need further improvements.
It can be used for testing like this:
```
\documentclass[10pt]{article}
\usepackage[customdriver=hhitex]{hyperref}
```


## Authors
Martin Ruckert, Karl Berry, Ulrike Fischer

## WWW
http://hint.userweb.mwn.de/

## License
All the executables and the code you find here is in the public domain unless stated otherwise. There is no implied warranty for any function not even against
malfunctioning. These are beta test versions.

