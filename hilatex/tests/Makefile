
LTXFILES=ltxfloat1.tex\
	ltximage1.tex ltximage2.tex\
	ltxlinks1.tex ltxlinks2.tex ltxlinks3.tex\
	ltxlinks4.tex ltxlinks5.tex ltxlinks6.tex

TEXFILES=plainfloat1.tex\
	plainimage1.tex plainimage2.tex plainimage3.tex\
	plainimage4.tex plainimage5.tex\
	plainlinks1.tex

HNTFILES=$(LTXFILES:.tex=.hnt) $(TEXFILES:.tex=.hnt)

HINTFILES=$(LTXFILES:.tex=.hint) $(TEXFILES:.tex=.hint)

PDFFILES=$(LTXFILES:.tex=.pdf) $(TEXFILES:.tex=.pdf)

all: $(HNTFILES) $(PDFFILES) $(HINTFILES)

ltx%.hnt: ltx%.tex
	hilatex $<
	hilatex $<
	hilatex $<

plain%.hnt: plain%.tex
	hitex $<

ltx%.pdf: ltx%.tex
	pdflatex $<
	pdflatex $<
	pdflatex $<

plain%.pdf: plain%.tex
	pdftex $<
	pdftex $<
	pdftex $<

%.hint: %.hnt
	stretch $<

ltxlinks3.pdf: ltxlinks3.bbl
ltxlinks3.hnt: ltxlinks3.bbl

%.bbl: %.bib %.aux
	bibtex $*



.PHONY: clean
clean:
	rm -f $(HNTFILES) $(PDFFILES) $(HINTFILES)
	rm -f *.aux *.log  *.out *.lof *.toc *.bbl
	rm -f *~
