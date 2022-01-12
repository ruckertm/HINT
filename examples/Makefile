
TEX=	mfpreface.tex \
	png.tex jpg.tex image.tex head.tex \
	math.tex leaders.tex ligature.tex 

TEX_EXTRA= ctex.tex format.tex

HNT_EXTRA= cwebman-ru.hnt

IMAGE= A.png A.jpg Loewe.jpg Head.jpg

TEXFLAGS = -mfmode=mobile -no-empty-page -hyphenate-first-word
#leaders.tex

#	simple.tex fonts.tex paging.tex hset.tex vset.tex vpack.tex baseline.tex \
#	paragraph.tex math.tex display.tex short.tex hyphen.tex hello.tex \
#	param.tex ligature.tex long.tex leaders.tex language.tex \
#	ctexshort.tex ctex.tex footnote.tex \

LATEX= ueb2.tex sample2e.tex

HNT=  $(LATEX:.tex=.hnt)  $(TEX:.tex=.hnt) $(TEX_EXTRA:.tex=.hnt)
HINT=  $(LATEX:.tex=.HINT)  $(TEX:.tex=.HINT) $(TEX_EXTRA:.tex=.HINT)

all: $(HNT)

$(TEX:.tex=.hnt): %.hnt: %.tex 
	hitex $(TEXFLAGS) $<


$(LATEX:.tex=.hnt): %.hnt: %.tex 
	hilatex $(TEXFLAGS) $<

%.HINT: %.hnt
	../../hint/format/stretch $<

FORMAT_INCLUDE= cwebmac.tex format.sty format.toc format.aux \
	format.red.srt format.wrt.srt format.get.srt format.put.srt \
	format.scn format.bbl format.ind 

$(FORMAT_INCLUDE):$(addprefix ../../hint/format/,$(FORMAT_INCLUDE))
	$(MAKE) -C ../../hint/format format.dvi
	cp  $^ .

format.hnt:
	$(MAKE) -C ../../hint/format format.hnt
	cp ../../hint/format/format.hnt .

ctex.hnt:
	$(MAKE) -C ../../hint/web2w ctex.hnt
	cp ../../hint/web2w/ctex.hnt .


mf.base: modes.mf
	echo mf.ini | inimf

cmmf.base: modes.mf
	echo cmmf.ini | inimf

www: all
	cp $(HNT)$(HNT_EXTRA) /c/home/hint/www/examples
	cp $(TEX) $(LATEX)  /c/home/hint/www/examples
	cp $(IMAGE)  /c/home/hint/www/examples



clean:
	rm -f *.dvi *.aux *.log *.pdf
	rm -rf *.abs
	rm -f \#* *~
	rm -f $(HINT) $(HNT)

