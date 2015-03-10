CPP = /usr/bin/g++
CFLAGS = --std=c++11 -Wall
mkfile_path := /home/alex/gcm-3d.next/src/
INCLUDEDIR = $(mkfile_path)
SOURCEDIR = $(INCLUDEDIR)

SOURCES = $(SOURCEDIR)libgcm/rheologyModels/rightHandSideSetters/MaxwellViscosityRightHandSideSetter.cpp\
          $(SOURCEDIR)libgcm/solvers/rightHandSideSolvers/FirstOrderRightHandSideSolver.cpp\
          $(SOURCEDIR)libgcm/solvers/rightHandSideSolvers/SecondOrderRightHandSideSolver.cpp\
          $(SOURCEDIR)libgcm/nodes/IdealElasticNode.cpp\
          $(SOURCEDIR)libgcm/nodes/CalcNode.cpp\
          $(SOURCEDIR)libgcm/util/Exception.cpp\
          RightHandSideSetterTest.cpp


OBJECTS = $(SOURCES:%.cpp=%.o)

%.o: %.cpp
	$(CPP) $(CFLAGS) -I $(INCLUDEDIR) -c $< -o $@

RightHandSideSetterTest: $(OBJECTS)
	$(CPP) $(OBJECTS) -O0 --std=c++11 -I $(INCLUDEDIR) -o $@
	./$@

clean:
	rm -f $(OBJECTS)
	rm -f RightHandSideSetterTest