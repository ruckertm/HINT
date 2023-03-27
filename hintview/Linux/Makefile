
# testing gtk options
ifndef WITH_GTK
WITH_GTK=0
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
$(error "Valid values for WITH_GTK are 0, 2 or 3")
endif

CC = gcc
CFLAGS = -g -O0 -ggdb -DDEBUG -Wall -I../backend
LDFLAGS = -g -Og
#GL_DEFINES = -DGLEW_STATIC -DTW_NO_DIRECT3D -DTW_NO_LIB_PRAGMA -DTW_STATIC -D_CRT_SECURE_NO_WARNINGS

FT_INCLUDES = -I/usr/include/freetype2
GL_INCLUDES = $(FT_INCLUDES)


HFILES =     hint.h htex.h format.h get.h basetypes.h error.h \
	     hrender.h rendernative.h hfonts.h

WFILES =     format.w hint.w htex.ch btex.w

OBJ=main.o  renderOGL.o get.o hint.o tables.o htex.o hrender.o hfonts.o

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

main.o: main.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $< 

hint.o: ../backend/hint.c
	$(CC) $(CFLAGS) -Wno-unused-but-set-variable -o $@ -c $<

htex.o: ../backend/htex.c
	$(CC) $(CFLAGS) -Wno-parentheses -Wno-unused-but-set-variable -Wno-maybe-uninitialized -o $@ -c $<

renderOGL.o: renderOGL.c
	$(CC) $(FT_INCLUDES) $(CFLAGS) -o $@ -c $<

hfonts.o: ../backend/hfonts.c
	$(CC) $(CFLAGS) $(FT_INCLUDES) -o $@ -c $<

%.o: ../backend/%.c 
	$(CC) $(CFLAGS) -o $@ -c $<

hintview: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(LIBS) $(GTK_LIBS) -o $@ 

SRC= $(OBJ:.o=.c) $(HFILES) main.h stb_image.h Makefile CMakeLists.txt
DIST_SRC = $(SRC:%=src/%)
DIST_MAN = man/hintview.1

BINDIR=/usr/local/bin
MANDIR=/usr/local/man

install: hintview
	strip hintview
	install -t $(BINDIR) --mode=755 hintview
	install -t $(MANDIR)/man1 --mode=644 ../man/hintview.1

.PHONY: clean
clean:
	rm -f *.o *~ *.dvi *.log *.aux
	rm -f hintview


