
STRETCH=~/gitlab/hint/format/stretch
SHRINK=~/gitlab/hint/format/shrink


%.hnt: %.hint
	$(SHRINK) $<

%.hnt: %.tex
	hitex $<

%.hint: %.hnt
	$(STRETCH) $<

