
# testing gtk options
ifndef WITH_GTK
WITH_GTK = $(shell pkg-config --exists gtk+-3.0 && echo 3 || echo 0)
ifeq ($(WITH_GTK),0)
WITH_GTK = $(shell pkg-config --exists gtk+-2.0 && echo 2 || echo 0)
endif
endif

ifeq ($(WITH_GTK),0)

GTK_CFLAGS = -DWITH_GTK=0
GTL_LIBS = 
else ifeq ($(WITH_GTK),2)
PKGCONFIG = $(shell which pkg-config)
GTK_CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-2.0) -DWITH_GTK=2
GTK_LIBS = $(shell $(PKGCONFIG) --libs gtk+-2.0)
else ifeq ($(WITH_GTK),3)
PKGCONFIG = $(shell which pkg-config)
GTK_CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0) -DWITH_GTK=3
GTK_LIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0)
else
$(error "Valid values for WITH_GTK are 0, 2 or 3 not $(WITH_GTK)!")
endif

CC = gcc
ifdef DEBUG
CFLAGS = -g -O0 -ggdb -DDEBUG -Wall -I../backend
LDFLAGS = -g -Og -ggdb
else
CFLAGS = -O2 -Wall -I../backend
LDFLAGS = -O2
endif
#GL_DEFINES = -DGLEW_STATIC -DTW_NO_DIRECT3D -DTW_NO_LIB_PRAGMA -DTW_STATIC -D_CRT_SECURE_NO_WARNINGS

FT_INCLUDES = -I/usr/include/freetype2
GL_INCLUDES = $(FT_INCLUDES)


HFILES =     format.h get.h basetypes.h error.h \
	     hint.h rendernative.h

WFILES =     format.w hint.w

OBJ=main.o  renderOGL.o get.o hint.o tables.o

ifeq (Msys,$(shell uname -o))
LIBS= ../external/glfw-3.1.2/msys.build/src/libglfw3.a ../external/libglew.a  -lfreetype \
	       -lm -lz
#	 -ldl -lm -lX11 -lpthread -lXrandr -lXinerama -lXi -lXcursor -lGL -lz
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


