DIST=$(shell kpsewhich -var-value=TEXMFDIST)
BIN=$(shell kpsewhich -var-value=SELFAUTOLOC)

ifeq (Msys,$(shell uname -o))
DIST=$(patsubst C:%,/c%,$(DIST))
BIN=$(patsubst C:%,/c%,$(BIN))
endif

BASEDIR=$(DIST)/tex/hitex/base
CFGDIR=$(DIST)/tex/latex/graphics-cfg
TEX=$(shell which tex)
LINKDIR=$(dir $(TEX))

BASE= hitex.def hhitex.def hiltxpage.tex hilatex.ini
CFG= color.cfg graphics.cfg
$(BASEDIR):
	install -d $(BASEDIR)

$(CFGDIR):
	install -d $(CFGDIR)


.PHONY: install
install: $(BASE) $(CFG) $(BASEDIR) $(CFGDIR)
	install -t $(BASEDIR) --mode=644 $(BASE)
	install -t $(CFGDIR) --mode=644 $(CFG)
	$(BIN)/mktexlsr
