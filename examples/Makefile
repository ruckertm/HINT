
### TeX source files
TEX=	mfpreface.tex \
	png.tex jpg.tex image.tex head.tex \
	math.tex leaders.tex ligature.tex calibration.tex \
	vtop.tex fonts.tex \
	color0.tex color1.tex color2.tex color3.tex

### LaTeX source files
LATEX= ueb2.tex  insertions.tex  gerdoc.tex

### Images
IMAGE= A.png A.jpg Loewe.jpg Head.jpg

### .hnt files that can be made directly from the source files
HNT=  $(LATEX:.tex=.hnt)  $(TEX:.tex=.hnt)

### .hnt files that need special make instructions
HNT_EXTRA=The_Call_to_the_Wild.hnt bible.hnt \
	ctex.hnt format.hnt sample2e.hnt \
	hintview.hnt

### .hint files are made from .hnt files using stretch
HINT=  $(LATEX:.tex=.hint) $(TEX:.tex=.hint) $(HNT_EXTRA:.hnt=.hint)

### standard flags to use when generating .hnt files.
TEXFLAGS = -mfmode=mobile -no-empty-page -hyphenate-first-word 

all: all_tex all_latex all_extra

all_tex:  $(TEX:.tex=.hnt)

all_latex:  $(LATEX:.tex=.hnt)

all_extra: $(HNT_EXTRA)

### TeX
$(TEX:.tex=.hnt): %.hnt: %.tex 
	hitex $(TEXFLAGS) $<

### LaTeX
$(LATEX:.tex=.hnt): %.hnt: %.tex 
	hilatex $(TEXFLAGS) $<

### Extra

EXTRA_DIR= ~/gitlab/hint/examples

.PHONY:  $(HNT_EXTRA)

The_Call_to_the_Wild.hnt:
	$(MAKE) -C $(EXTRA_DIR) $@
	cp  $(EXTRA_DIR)/$@ .

bible.hnt:
	$(MAKE) -C $(EXTRA_DIR) $@
	cp  $(EXTRA_DIR)/$@ .

ctex.hnt: 
	$(MAKE) -C $(EXTRA_DIR) $@
	cp  $(EXTRA_DIR)/$@ .

format.hnt: 
	$(MAKE) -C $(EXTRA_DIR) $@
	cp  $(EXTRA_DIR)/$@ .

### sample2e.tex is part of te TeX Live distribution
sample2e.hnt:
	hilatex $(TEXFLAGS) sample2e.tex

### hintview.tex is the hintview Linux man page
hintview.hnt:../hintview/Linux/hintview.tex 
	$(MAKE) -C ../hintview/Linux $@
	cp  ../hintview/Linux/$@ .

WWW_DIR= ~/gitlab/hint/www/examples

www: all
	cp $(HNT) $(HNT_EXTRA) $(WWW_DIR)
	cp $(TEX) $(LATEX) $(WWW_DIR)
	cp $(IMAGE) $(WWW_DIR)

clean:
	rm -f *.dvi *.aux *.log *.pdf
	rm -rf *.abs
	rm -f \#* *~
	rm -f $(HINT) $(HNT)

