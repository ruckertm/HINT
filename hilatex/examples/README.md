# TeX example and test files

## Description
These files contain different examples.
Files named plain*.tex (plain TeX files) 
are processed by tex, pdftex, or hitex. 
They illustrate or test various features. For example
plainlinks1.tex is the most simple program to test links.
The number preceeding the .tex enumerate the examples for
the same feature in increasing complexity.

For each plain*.tex file the is a ltx*.tex file trying to
achive the same result using LaTeX syntax. These files
must be processed by latex, pdflatex, or hilatex.


### plainlinks1.tex ltxlinks1.tex
The first page contains three clickable links to the next three pages
using textual labels to identify the destinations.
The plain TeX file works for hitex, the LaTeX file works for pdflatex.
Both examples and the necessary tex code (in the distribution) should
be changed so that both files work for both engines.

### ltxlinks2.tex
This example tests sections and subsections, a table of content and outlines.

### ltxlinks3.tex ltxlink3.bib ltxlinks3.bbl
This example tests bibliograpy links. The file ltxlinks3.bbl can be generated using bibtex.

### ltxlinks4.tex
This example test links to figures. There are still some problems:
Figures work only whit Placement = h (here).
Floats dont work (see next example).

The caption is not centered on the page and captions are not broken into
multiple lines if the space on the page requires it. In the list of figures,
captions are broken into several lines.

### ltxlinks5.tex
This example tests links to displayed equations and with it the
generation of pages that start in the middle of a paragraph.
The current algorithm works quite well in most circumstances,
but there is still room for improvement.

### ltxfloat1.tex
This example tries to do floats, but hilatex does generate LaTeX errors.

## Examples still needed:

### Backreferences from the bibliography

### Links to tables

### Links from the Index

### Links to footnotes (not very important I guess).

### References to pages (there are no page numbers in a HINT file)

### Outlines that contain non ASCII characters like in "München".

### Outlines that contain special contructs like \TeX or \LaTeX or $\sum_{i\to\infty} a_i$.

### Outlines with no consecutive depth levels

## Authors
Martin Ruckert, Karl Berry

## WWW
http://hint.userweb.mwn.de/

## License
All the executables and the code you find here is in the public domain unless stated otherwise. There is no implied warranty for any function not even against
malfunctioning. These are beta test versions.

