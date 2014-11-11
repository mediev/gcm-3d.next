PLFLAGS=-halt-on-error

default: build

build:
	

blueprint:
	pdflatex ${PLFLAGS} spaceship.tex
	pdflatex ${PLFLAGS} spaceship.tex

clean:
	rm -f *.log *.aux *.tdo *.toc *.out
