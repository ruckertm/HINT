
PKG_CONFIG ?= pkg-config

GTK_CFLAGS = $(shell $(PKG_CONFIG) --cflags gtk+-3.0) 
GTK_LIBS = $(shell $(PKG_CONFIG) --libs gtk+-3.0)


CC= gcc
ifdef DEBUG
CFLAGS = -g -O0 -ggdb -DDEBUG -DHAVE_HINT_ERROR -DHAVE_HINT_MESSAGE -Wall -I../backend
LDFLAGS = -g -Og -ggdb
else
CFLAGS = -O2 -Wall -I../backend -DHAVE_HINT_ERROR -DHAVE_HINT_MESSAGE
LDFLAGS = -O2
endif


ifeq (Msys,$(shell uname -o))
FT_INCLUDES = -I/mingw64/include/freetype2 
LIBS = -lglew32 -lopengl32 -lfreetype -lz -lm
else
FT_INCLUDES = -I/usr/include/freetype2
LIBS = -lGLEW -lGL -lfreetype -lz -lm
endif


SRC= about.c main.c preferences.c resources.c settings.c \
	header.c outline.c renderOGL.c search.c 

OBJ= main.o renderOGL.o get.o hint.o tables.o \
 search.o  outline.o header.o settings.o about.o\
 resources.o preferences.o


all: hintview

%.c: %.w
	echo running ctangle disabled

-include .depend



.depend: $(SRC)
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

search.o: search.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $< 

search: search.o
	$(CC) $(LDFLAGS) $< $(GTK_LIBS) -o $@


outline.o: outline.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $< 

outline: outline.o
	$(CC) $(LDFLAGS) $< $(GTK_LIBS) -o $@

header.o: header.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $< 

header: header.o
	$(CC) $(LDFLAGS) $< $(GTK_LIBS) -o $@

preferences.o: preferences.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $< 

preferences: preferences.o
	$(CC) $(LDFLAGS) $< $(GTK_LIBS) -o $@

about.o: about.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $< 

about: about.o
	$(CC) $(LDFLAGS) $< $(GTK_LIBS) -o $@


resources.o: resources.c resources.h
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $< 

resources.c: resources.xml # help.sgml
	glib-compile-resources --generate-source  resources.xml 

resources.h: resources.xml
	glib-compile-resources --generate-header  resources.xml 

settings.o: settings.c
	$(CC) $(CFLAGS) $(GTK_CFLAGS) -o $@ -c $< 

settings: settings.o
	$(CC) $(LDFLAGS) $< $(GTK_LIBS) -o $@

BINDIR=/usr/local/bin
MANDIR=/usr/local/man

hintview.hnt: hintview.tex
	hitex hintview.tex

install: hintview
	strip hintview
	install -t $(BINDIR) --mode=755 hintview
	install -t $(MANDIR)/man1 --mode=644 hintview.1



.PHONY: install_schema
install_schema: edu.hm.cs.hintview.gschema.xml
	sudo install edu.hm.cs.hintview.gschema.xml /usr/share/glib-2.0/schemas/
	sudo glib-compile-schemas /usr/share/glib-2.0/schemas/



ICON_DIR=/usr/share/icons/hicolor
ICON_NAME=mimetypes/x-hintview.png
# Works also: ICON_NAME=apps/x-hintview.png
#ICON_SRC= ../resources/logo/HINTLogoBuchGrey
ICON_SRC= ../resources/logo/HINTLogoBuchFG
ICON_SIZE = 16 32 48 64 128 256 512

ICONS = $(patsubst %,$(ICON_SRC)%.png,$(ICON_SIZE))


.PHONY: install_icons
install_icons: hintview.xml
	sudo install hintview.xml /usr/share/mime/packages
	sudo update-mime-database /usr/share/mime/
	for i in $(ICON_SIZE) ; do\
	  sudo install $(ICON_SRC)$$i.png $(ICON_DIR)/"$$i"x"$$i"/$(ICON_NAME) ;\
	done
	sudo gtk-update-icon-cache  $(ICON_DIR)

.PHONY: delete_icons
delete_icons:
	for i in $(ICON_SIZE) ; do\
	  sudo rm -f $(ICON_DIR)/"$$i"x"$$i"/$(ICON_NAME) ;\
	done
	sudo gtk-update-icon-cache  $(ICON_DIR)


.PHONY: clean
clean:
	rm -rf *~ *.o *.log *.w
	rm -rf hintview .depend TAGS
