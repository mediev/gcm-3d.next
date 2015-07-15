CPP = mpic++
CFLAGS = --std=c++11 -Wall -g
INCLUDEDIR = /home/alex/work/gcm-3d.next/src/

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
	$(CPP) $(CFLAGS) -I$(INCLUDEDIR) -c $< -o $@

RightHandSideSetterTest: $(OBJECTS)
	$(CPP) $(OBJECTS) --std=c++11 -I$(INCLUDEDIR) -o $@
	./$@ && gnuplot plotter


DispatcherTest: DispatcherTest.cpp 
	$(CPP) DispatcherTest.cpp --std=c++11 -I$(INCLUDEDIR) -o $@
	./$@

clean:
	rm -f $(OBJECTS)
	rm -f RightHandSideSetterTest
	rm -f DispatcherTest