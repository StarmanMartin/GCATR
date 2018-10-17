output = .output
rnwfile = min_tex
backup = .backup

all:
	Rscript -e "library(knitr); knit('$(rnwfile).Rnw')"
	-mkdir $(output)
	-rm $(output)/figure
	-cp *.sty $(output)
	-cp -r figure/ $(output)
	-mv *.tex *.pdf *.eps $(output)
	cd $(output); texify --run-viewer --pdf $(rnwfile).tex 

tex:
	cd $(output); texify --run-viewer --pdf $(rnwfile).tex

clean:
	-rm $(output)/*

backup:
	-mkdir $(backup)
	cp  $(output)/$(rnwfile).pdf $(backup)/$(rnwfile).pdf