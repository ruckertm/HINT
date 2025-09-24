


PKGCONFIG = $(shell which pkg-config)
GTK_CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0) -DWITH_GTK=3
GTK_LIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0)

FT_INCLUDES = -I/usr/include/freetype2

CC= gcc
CFLAGS= -ggdb -O0 -DDEBUG -Wall -I../backend $(FT_INCLUDES)

all: hintview

%.c: %.w
	echo running ctangle disabled

hintview.o: hintview.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -c $< -o $@

renderOGL.o: renderOGL.c
	$(CC) $(CFLAGS) -c $< -o $@

hint.o: ../backend/hint.c
	$(CC) $(CFLAGS) $(FT_INCLUDES) -o $@ -c $<


hintview: hintview.o renderOGL.o hint.o
	$(CC) hintview.o renderOGL.o hint.o $(GTK_LIBS) -lGLEW -lGL -lm -o $@

clean:
	rm -rf *~ *.o
	rm -rf hintview
