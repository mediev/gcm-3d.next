CPP    = /usr/bin/g++
CFLAGS = --std=c++11 -Wall
INCLUDEDIR = $(PWD)/../

SOURCES = $(shell find $(SOURCEDIR) -name '*.cpp')
OBJECTS = $(SOURCES:%.cpp=%.o)

all: $(OBJECTS)

%.o: %.cpp
	$(CPP) $(CFLAGS) -I $(INCLUDEDIR) -c $< -o $@

clean:
	rm -f $(OBJECTS)
