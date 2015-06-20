CPP    = mpic++
CFLAGS = --std=c++11 -Wall -g
LIBFLAGS = -lgsl -lgslcblas -lm -lgmsh -lvtkCommonCore-6.0 -lvtkFiltersCore-6.0 -lvtkIOCore-6.0 -lvtkIOXML-6.0 -lvtkCommonDataModel-6.0
INCLUDEFLAGS = -I/home/mediev/projects-repo/gcm-3d-mediev/gcm-3d.next/src -I/usr/include/gmsh -I/usr/include/vtk-6.0
SOURCEDIR = src/libgcm

SOURCES = $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS = $(SOURCES:%.cpp=%.o)

EXECUTABLE=gcm

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CPP) $(OBJECTS) -o $@ $(LIBFLAGS)

%.o: %.cpp
	$(CPP) $(CFLAGS) $(INCLUDEFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(EXECUTABLE)
	rm -f models/*.msh
	rm -f *.vtu *.vts
