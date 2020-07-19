
TEX=	mfpreface.tex \
	bmp.tex png.tex jpg.tex image.tex head.tex \
	ctex.tex \
	math.tex leaders.tex

TEXFLAGS = -m mobile -e -f
#leaders.tex

#	simple.tex fonts.tex paging.tex hset.tex vset.tex vpack.tex baseline.tex \
#	paragraph.tex math.tex display.tex short.tex hyphen.tex hello.tex \
#	param.tex ligature.tex long.tex leaders.tex language.tex \
#	ctexshort.tex ctex.tex footnote.tex \

LATEX= ueb2.tex sample2e.tex

all:  $(LATEX:.tex=.hnt)  $(TEX:.tex=.hnt)

$(TEX:.tex=.hnt): %.hnt: %.tex 
	hitex $(TEXFLAGS) $<

$(LATEX:.tex=.hnt): %.hnt: %.tex 
	hilatex $(TEXFLAGS) $<

%.HINT: %.hnt
	../../hint/format/stretch $<

mf.base: modes.mf
	echo mf.ini | inimf

cmmf.base: modes.mf
	echo cmmf.ini | inimf

clean:
	rm -f *.dvi *.hnt *.aux *.log
	rm -rf *.abs
	rm -f \#* *~
	rm -f $(LATEX:.tex=.HINT)  $(TEX:.tex=.HINT)
