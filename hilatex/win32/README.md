# Binaries for WIN32

## Description
The binaries you find here are the most recent binaries available.
The stable version can be found on the HintView home page:
http://hint.userweb.mwn.de/hint/hintview.html 
 

## Installation

### hitex.exe
The hitex executable uses the kpathsearch library. This library is used
to find and open files. For this job, it must be installed in the 
correct directory. So you need an instalation of TeX Live 2022 or newer
and install hitex in the same directory where the other executables
of TeX Live are installed. On my machine, binaries of TeX Live
are installed in C:\texlive\2022\bin\win32\
and this is the directory where hitex.exe must be installed as well.


### hilatex.exe
There is no separate binary for LaTeX.
Since links do not work well in Windows hilatex.exe is just a copy of hitex.exe.
Running hitex under the name hilatex will cause hitex to load a different
format file (see the ../format directory).

### hintview.exe
Just download and move the executable to a place on your path.

Even if not on your path, for example on your Desktop, you can start
the executable with a simple double click.

You can also right click on a .hnt file, select "Open with",
select "Choose another app", scroll down, select "More apps",
scroll down (be patient, we are almost there), choose "Look for another
app on this PC",  search for
the program you have just downloaded, select it and don't forget to
check the "Always use this app to open .hnt files" box before
you click the OK button.

## Authors
Martin Ruckert, Hochschule München,

## WWW
http://hint.userweb.mwn.de/

## License
All the executables and the code you find here is in the public domain unless stated otherwise. There is no implied warranty for any function not even against
malfunctioning. These are beta test versions.

