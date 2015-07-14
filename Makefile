CPP    = mpic++
CFLAGS = --std=c++11 -Wall -g
LIBFLAGS = -lgsl -lgslcblas -lm -lgmsh -lvtkCommonCore-6.0 -lvtkFiltersCore-6.0 -lvtkIOCore-6.0 -lvtkIOXML-6.0 -lvtkCommonDataModel-6.0 -L/usr/lib/x86_64-linux-gnu -lmetis
INCLUDEFLAGS = -I/home/alex/work/gcm-3d.next/src -I/usr/include/gmsh -I/usr/include/vtk-6.0
SOURCEDIR = src/libgcm
TESTDIR = src/tests

SOURCES = $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS = $(SOURCES:%.cpp=%.o)

# the whole project

EXECUTABLE=gcm

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CPP) $(CFLAGS) $(OBJECTS) -o $@ $(LIBFLAGS)

%.o: %.cpp
	$(CPP) $(CFLAGS) $(INCLUDEFLAGS) -c $< -o $@

# the test on Dispatcher

DISPATCHER=dispatcherTest

$(SOURCEDIR)/Dispatcher.o: $(SOURCEDIR)/Dispatcher.cpp
	$(CPP) $(CFLAGS) $(INCLUDEFLAGS) -c $< -o $@

$(DISPATCHER): $(TESTDIR)/DispatcherTest.cpp $(SOURCEDIR)/Dispatcher.o
	$(CPP) $(CFLAGS) $(INCLUDEFLAGS) $(TESTDIR)/DispatcherTest.cpp $(SOURCEDIR)/Dispatcher.o -o $@ $(LIBFLAGS)


clean:
	rm -f $(OBJECTS)
	rm -f $(EXECUTABLE)
	rm -f $(DISPATCHER)
	rm -f models/*.msh
	rm -f *.vtu *.vts
