CC = gcc
ifdef DEBUG
CFLAGS = -g -O0 -ggdb -DDEBUG -Wall -I../backend
LDFLAGS = -g -Og -ggdb
else
CFLAGS = -O2 -Wall -I../backend
LDFLAGS = -O2
endif

FT_INCLUDES = -I/usr/include/freetype2
GL_INCLUDES = $(FT_INCLUDES)


HFILES =     format.h get.h basetypes.h error.h \
	     hint.h rendernative.h

WFILES =     format.w hint.w

OBJ=main.o  renderOGL.o get.o hint.o tables.o

ifeq (Msys,$(shell uname -o))
LIBS= ../external/glfw-3.1.2/msys.build/src/libglfw3.a ../external/libglew.a  -lfreetype \
	       -lm -lz
else
LIBS= -lglfw -lGLEW -ldl -lfreetype -lX11 -lXrandr -lXinerama -lXi -lXcursor -lGL -lz -lpthread -lm 
endif

all: hintview

.SUFFIXES:            # Delete the default suffixes

%.c: %.w
	echo running ctangle disabled

-include .depend

.depend: main.c  renderOGL.c 
	$(CC) -I../backend -MM *.c  > $@ || true

main.o: main.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $< 

hint.o: ../backend/hint.c
	$(CC) $(CFLAGS) $(FT_INCLUDES) -o $@ -c $<

renderOGL.o: renderOGL.c
	$(CC) $(FT_INCLUDES) $(CFLAGS) -o $@ -c $<

%.o: ../backend/%.c 
	$(CC) $(CFLAGS) $(FT_INCLUDES)  -o $@ -c $<

# copy the .w files for gdb
hintview: $(OBJ)
	cp ../backend/*.w .
	$(CC) $(LDFLAGS) $(OBJ) $(LIBS) $(GTK_LIBS) -o $@ 

SRC= $(OBJ:.o=.c) $(HFILES) main.h stb_image.h Makefile CMakeLists.txt
DIST_SRC = $(SRC:%=src/%)
DIST_MAN = man/hintview.1

BINDIR=/usr/local/bin
MANDIR=/usr/local/man

install: hintview
	strip hintview
	install -t $(BINDIR) --mode=755 hintview
	install -t $(MANDIR)/man1 --mode=644 hintview.1

.PHONY: clean
clean:
	rm -f *.o *~ *.dvi *.log *.aux
	rm -f hintview


