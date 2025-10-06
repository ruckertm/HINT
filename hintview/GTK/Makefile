


PKGCONFIG = $(shell which pkg-config)
GTK_CFLAGS = $(shell $(PKGCONFIG) --cflags gtk+-3.0) -DWITH_GTK=3
GTK_LIBS = $(shell $(PKGCONFIG) --libs gtk+-3.0)


CC= gcc
ifdef DEBUG
CFLAGS = -g -O0 -ggdb -DDEBUG -Wall -I../backend
LDFLAGS = -g -Og -ggdb
else
CFLAGS = -O2 -Wall -I../backend
LDFLAGS = -O2
endif


ifeq (Msys,$(shell uname -o))
FT_INCLUDES = -I/mingw64/include/freetype2 
LIBS = -lfreetype -lopengl32 -lglew32 -lz -lm
else
FT_INCLUDES = -I/usr/include/freetype2
LIBS = -lGLEW -lGL -lfreetype -lz -lm
endif


OBJ= main.o renderOGL.o get.o hint.o tables.o \
 search-bar.o  outline.o header.o settings.o dialog.o

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


message.o: message.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $< 

message: message.o
	$(CC) $(LDFLAGS) $< $(GTK_LIBS) -o $@

search-bar.o: search-bar.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $< 

search-bar: search-bar.o
	$(CC) $(LDFLAGS) $< $(GTK_LIBS) -o $@


outline.o: outline.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $< 

outline: outline.o
	$(CC) $(LDFLAGS) $< $(GTK_LIBS) -o $@

header.o: header.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $< 

header: header.o
	$(CC) $(LDFLAGS) $< $(GTK_LIBS) -o $@

dialog.o: dialog.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $< 

dialog: dialog.o
	$(CC) $(LDFLAGS) $< $(GTK_LIBS) -o $@

settings.o: settings.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $< 

settings: settings.o
	$(CC) $(LDFLAGS) $< $(GTK_LIBS) -o $@

.PHONY: install_schema
install_schema: edu.hm.cs.hintview.gschema.xml
	sudo install edu.hm.cs.hintview.gschema.xml /usr/share/glib-2.0/schemas/
	sudo glib-compile-schemas /usr/share/glib-2.0/schemas/

clean:
	rm -rf *~ *.o
	rm -rf hintview
