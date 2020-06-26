
TEX=  mfpreface.tex \
	bmp.tex png.tex jpg.tex image.tex head.tex \
	ctex.tex \
	math.tex leaders.tex

#	simple.tex fonts.tex paging.tex hset.tex vset.tex vpack.tex baseline.tex \
#	paragraph.tex math.tex display.tex short.tex hyphen.tex hello.tex \
#	param.tex ligature.tex long.tex leaders.tex language.tex \
#	ctexshort.tex ctex.tex footnote.tex \

LATEX= ueb2.tex sample2e.tex

all:  $(LATEX:.tex=.hnt)  $(TEX:.tex=.hnt)

$(TEX:.tex=.hnt): %.hnt: %.tex 
	hitex $<

$(LATEX:.tex=.hnt): %.hnt: %.tex 
	hilatex $<

%.HINT: %.hnt
	../../hint/format/stretch $<



clean:
	rm -f *.dvi *.hnt *.aux *.log
	rm -rf *.abs
	rm -f \#* *~
	rm -f $(LATEX:.tex=.HINT)  $(TEX:.tex=.HINT)
