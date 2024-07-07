# This file creates the tprof and texprof executable files
# and installs them with the install_bin target.
# This file creates the texprof.fmt and latexprof.fmt format filrd
# and installs them with the install_fmt target.

# The commands are tested under linux with GNU make and GNU gcc.
# They might need modifications if you use them using other operating
# systems or other tools.

### Tools

## The cweb system
# available with TeX Live or from http://www.literateprogramming.com/
CTANGLE=ctangle
CWEAVE=cweave

## Tools you need to build the executables

# The C compiler
CC=gcc
CFLAGS= -O2 -DINIT -Wall -I.
# To suppress warnings when compiling texprof these additional flags
# can be used
TEXFLAGS= -Wno-unused-result -Wno-parentheses -Wno-maybe-uninitialized -Wno-unused-function -Wno-unused-variable

# The kpathsea library
# This is the most difficult to get item because it is usualy only
# part of the TeX Live build process.
# You can get the sources from https://ctan.org/pkg/kpathsea or
# search for a ready made instance on the internet.
# the following variables reflect my installation

# the directory with the header files: kpathsea.h
KPATHSEA_H_DIR=/usr/local/include/kpathsea/

# the directory with the library files: libkpathsea.a and libkpathsea.la
KPATHSEA_LIB_DIR=/usr/local/lib/x86_64-pc-linux-gnu/


## Tools you need to build the documentation

# The TeX system
# The TeX system is a complicated system of files and tools
# it is available from TeX Live https://www.tug.org/texlive/
TEX=tex
PDFTEX=pdftex
MKINDEX=mkindex


## Tools to install the binaries and format files

# install is part of the operating system
# you might need su or sudo to get the necessary access rights
# when using install.
INSTALL=install

# to obtain the path of the installation directories
# which is part of the operating system
# kpsewhich is part of the TeX system 
WHICH=which
KPSEWHICH=kpsewhich

### The top level targets

all: install_bin install_fmt

### Building 

### Step 1: Extracting the .c and .tex files

# produce tprof.c and texprof.c from the .w files with CTANGLE

tprof.c: ../tprof.w
	$(CTANGLE) ../tprof.w

texprof.c: ../texprof.w
	$(CTANGLE) ../texprof.w

# produce tprof.tex and texprof.tex from the .w files with CWEAVE

tprof.tex tprof.scn tprof.idx: ../tprof.w
	$(CWEAVE) ../tprof.w

texprof.tex texprof.scn texprof.idx: ../texprof.w
	$(CWEAVE) ../texprof.w


### Step 2: Compiling the c files

tprof: tprof.c
	$(CC) $(CFLAGS) -o tprof tprof.c

texprof.o: texprof.c
	$(CC) $(CFLAGS) $(TEXFLAGS) -I$(KPATHSEA_H_DIR) -c -o texprof.o texprof.c

md5.o: md5.c md5.h
	$(CC) $(CFLAGS) -c -o md5.o md5.c

texprof: texprof.o md5.o
	$(CC) $(CFLAGS) texprof.o md5.o -L$(KPATHSEA_LIB_DIR) -lkpathsea -lm -o texprof


### Step 4. Installing the binaries

# For the binaries to find their input files
# they must be part of the TeX instalation tree.
# I assume a normal TeX Live installation

# This tries to set the directories

# the root of the TeX instalation
SYSVAR=$(shell kpsewhich -var-value=TEXMFSYSVAR)
# the name of the TeX engine
ENGINE=hitex
# the directory for formats
FMTDIR=$(SYSVAR)/web2c/$(ENGINE)
# the directory where the system finds executables
TEX=$(shell which tex)
# the directory for where the system finds executables
#usualy has only links to the binaries
LINKDIR=$(dir $(TEX))
# the directory where the binaries are in the TeX installation
BINDIR=$(SYSVAR:/texmf-var=/bin/x86_64-linux)

install_bin: texprof tprof
	install -t $(BINDIR) --mode=755 texprof tprof
	ln -s -f $(BINDIR)/texprof $(LINKDIR)latexprof
	ln -s -f $(BINDIR)/texprof $(LINKDIR)texprof
	ln -s -f $(BINDIR)/tprof $(LINKDIR)tprof
	touch install_bin


### Step 5: Building the format files

texprof.fmt:  install_bin ../aux/texprof.ini
	$(BINDIR)/texprof -ini -etex -ltx ../aux/texprof.ini \\dump

latexprof.fmt: install_bin ../aux/latexprof.ini
	$(BINDIR)/texprof -ini -etex -ltx ../aux/latexprof.ini

### Step 6: Installing the format files

# if it does not exist we make the format directory
$(FMTDIR):
	if [ ! -d "$(FMTDIR)" ]; then install -d -C $(FMTDIR) ; fi

install_fmt: texprof.fmt latexprof.fmt $(FMTDIR)
	install -t $(FMTDIR) --mode=644  texprof.fmt latexprof.fmt
	$(BINDIR)/mktexlsr
	mv texprof.fmt latexprof.fmt ../fmt
	touch install_fmt


### Step 7: Building the documentation

# the first run of tex produces texprof.toc, the table of content
# so we run tex twice

texprof.pdf texprof.toc: texprof.tex texprof.scn texprof.idx
	$(PDFTEX) texprof
	$(PDFTEX) texprof

tprof.pdf tprof.aux: tprof.tex tprof.scn tprof.idx
	touch tprof.toc
	TEXINPUTS=".:../aux:" $(PDFTEX) tprof
	TEXINPUTS=".:../aux:" $(PDFTEX) tprof



### Cleaning up

clean:
	rm -f tprof.c texprof.c tprof.tex texprof.tex
	rm -f *.o texprof tprof
	rm -f *.aux *.get *.put *.red *.wrt *.idx *.inx *.toc *.log *.scn
	rm -f *.pdf *.dvi *.hnt
	rm -f texprof.tprof latexprof.tprof
	rm -f install_bin install_fmt rm 

