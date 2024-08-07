# HINT
Sources and Documentation for the HINT project.
The HINT projects home page is at https://hint.userweb.mwn.de/

## Directories

### examples
   example tex and latex files and the resulting HINT files (*.hnt)

### hilatex
   hilatex loads a format file to enable hitex to process
   standard LaTeX documents. The directory contains
   test cases, and supplemental code for using hilatex.
   The LaTeX support of hitex is still in its infancy, but growing.

### hintview
   hintview is a family of viewing applications for HINT files.
   the code for hintview is maintained in this directory.
   If you are looking for ready to use stable versions you should
   go to https://hint.userweb.mwn.de/hint/hintview.html and
   were you can get setup files or links to app-stores.

### texprof
    texprof is a profiler for TeX. It maps the runtime of TeX to
    the files, lines, and macros of TeX's input files.

## LICENSE

In this repository you find artifacts, notably source code,
from several sources that have different licenses attached.

- The files in hintview/external/ come from other projects
  and are here just for convenience. Each subdirectory there
  specifies its own license requirements.

- The files in hintview/backend/ fall into several categories:

  - stb_imgage.h is from the http://nothings.org/stb project
   and is in the public domain.

  - htex.w\
    htex.w is a derived work from D. E. Knuths tex.web and
    contains the license from the original tex.web file.

  - htex.c and htex.h\
    The files htex.c and htex.h are generated from htex.w
    using the program ctangle and are considered to be under
    the same license as htex.w

  - format.w and hint.w\
    These files are source files from the HINT project and
    contain an MIT/X11 license as in the file LICENSE.

  - Other files in hintview/backend/\
    All other files in hintview/backend are generated using
    the program ctangle from either format.w or hint.w and
    are considered to be under the same license as format.w or hint.w

- The files in Linux/, Android/, MacOS/, iOS/, and Win64/\
  These files implement the user interface of the various HINT
  file viewers. They currently have an MIT/X11 license included
  as in the file LICENSE;
  but future implementations of viewers might have
  different licenses attached.

- The artwork in hintview/resources/ is again under an MIT/X11 license
  as in the file LICENSE, but with the additional restriction
  that the use of the artwort is restricted to programs that
  have the sole purpose of displaying HINT files. All other uses
  require the written permission of the copyright holders.

- Any files not covered by the above that do not explicitly
  contain a different license statement are under an MIT/X11
  license as in the file LICENSE.
  

   
