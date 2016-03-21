all: full


simple:
	pdflatex report.tex

full: simple
	biber report
	make simple

clean:
	rm -rf _* auto *.aux *.bbl *.bcf *.blg *.log *.run.xml *.out *~
