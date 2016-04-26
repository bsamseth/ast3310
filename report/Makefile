all: full2 full3

simple2:
	pdflatex report.tex

simple3:
	pdflatex report3.tex

full2: simple2
	biber report
	make simple2

full3: simple3
	biber report3
	make simple3

clean:
	rm -rf _* auto *.aux *.bbl *.bcf *.blg *.log *.run.xml *.out *~ *.synctex.gz *.fdb_latexmk *.toc *.fls
