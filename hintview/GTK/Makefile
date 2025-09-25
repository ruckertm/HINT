


PKGCONFIG = $(shell which pkg-config)
GTK_CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0) -DWITH_GTK=3
GTK_LIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0)

FT_INCLUDES = -I/usr/include/freetype2

CC= gcc
ifdef DEBUG
CFLAGS = -g -O0 -ggdb -DDEBUG -Wall -I../backend
LDFLAGS = -g -Og -ggdb
else
CFLAGS = -O2 -Wall -I../backend
LDFLAGS = -O2
endif

LIBS = -lGLEW -lGL -lfreetype -lz -lm

OBJ= main.o renderOGL.o get.o hint.o tables.o

all: hintview

%.c: %.w
	echo running ctangle disabled

-include .depend

.depend: main.c  renderOGL.c 
	$(CC) -I../backend -MM *.c  > $@ || true

main.o: main.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $< 

renderOGL.o: renderOGL.c
	$(CC) $(CFLAGS) $(FT_INCLUDES) -o $@ -c $< 

hint.o: ../backend/hint.c
	$(CC) $(CFLAGS) $(FT_INCLUDES) -o $@ -c $<

%.o: ../backend/%.c 
	$(CC) $(CFLAGS) $(FT_INCLUDES)  -o $@ -c $<

hintview: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(GTK_LIBS) $(LIBS) -o $@
	cp ../backend/*.w .

clean:
	rm -rf *~ *.o
	rm -rf hintview
