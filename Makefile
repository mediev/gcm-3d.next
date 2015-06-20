CPP    = /usr/bin/g++
CFLAGS = --std=c++11 -Wall -g
LIBFLAGS = -lgsl -lgslcblas -lm -lgmsh
INCLUDEDIR = /home/mediev/projects-repo/gcm-3d-mediev/gcm-3d.next/src /usr/include/gmsh
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
	rm -f models/*.msh
