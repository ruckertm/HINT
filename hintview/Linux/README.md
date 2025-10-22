## HINT
Sources and Documentation for Viewing HINT files under Linux.

This implementation uses GTK-3 to build the user interface for hintview.
It

### Makefile
Controls the making of the hintview application.

In addition to the files in this directory, the files in the ../backend
and ../resources directory are required. 


### hintview.1
The man page for hintview

### hintview.tex
The man page for hintview as a TeX file. Use "hitex hintview" to get the HINT version of the manual page.

### hintview.spec
Packaging script for use with `rpmbuild` and `debbuild`

### main.c and main.h
A short main program and its exported identifiers.

### renderOGL.c
The rendering frontend using OpenGL.

### gui.h
Function prototypes for the following C files implementing the GUI.

### about.c
Implements the about box and other message boxes.

### header.c
Implements the header bar and the menu.

### preferences.c
Implements the preferences dialog.

### search.c
Implements the search window.

### outline.c
Implements the oulines window.

### header.c
Implements the header bar with buttons and menu.

### settings.c
Implements saving prefences to make them persistent.

### resources.xml
Used to generate resources.c and resources.h files.
Currently only a HINT logo from ../resources/logo/
is referenced.

### edu.hm.cs.hintview.gschema.xml
The schema used by gsettings and settings.c to store
and retrieve preferences.

