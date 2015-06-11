CPP    = /usr/bin/g++
CFLAGS = --std=c++11 -Wall
LIBFLAGS = -lgsl -lgslcblas -lm
INCLUDEDIR = /home/alex/work/gcm-3d.next/src
SOURCEDIR = src/libgcm

SOURCES = $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS = $(SOURCES:%.cpp=%.o)

EXECUTABLE=gcm

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CPP) $(OBJECTS) -o $@ $(LIBFLAGS)

%.o: %.cpp
	$(CPP) $(CFLAGS) -I $(INCLUDEDIR) -c $< -o $@

test: test.cpp
	g++ test.cpp -o test
	./test

clean:
	rm -f $(OBJECTS)
	rm -f $(EXECUTABLE)
