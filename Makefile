PLFLAGS=-halt-on-error

default: build

build:
	pdflatex ${PLFLAGS} spaceship.tex
	pdflatex ${PLFLAGS} spaceship.tex

clean:
	rm -f *.log *.aux *.tdo *.toc *.out
