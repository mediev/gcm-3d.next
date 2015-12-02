CPP = mpic++
CFLAGS = --std=c++11 -Wall -g
LIBFLAGS = -lgmsh -lmetis -lm -lvtkCommonCore-6.0 -lvtkFiltersCore-6.0 -lvtkIOCore-6.0 -lvtkIOXML-6.0 -lvtkCommonDataModel-6.0 -L/usr/lib/x86_64-linux-gnu
INCLUDEFLAGS = -I/home/mediev/projects-repo/gcm-3d-mediev/gcm-3d.next/src -I/usr/include/gmsh -I/usr/include/vtk-6.0
INCLUDEDIR = /home/mediev/projects-repo/gcm-3d-mediev/gcm-3d.next/src/

all: RightHandSideSetterTest DispatcherTest GmshTest 

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
	$(CPP) $(CFLAGS) -I$(INCLUDEDIR) $(INCLUDEFLAGS) -c $< -o $@

RightHandSideSetterTest: $(OBJECTS)
	$(CPP) $(OBJECTS) --std=c++11 $(INCLUDEFLAGS) -o $@

DispatcherTest: DispatcherTest.cpp 
	$(CPP) DispatcherTest.cpp $(INCLUDEDIR)/libgcm/Dispatcher.cpp --std=c++11 -I$(INCLUDEDIR) $(INCLUDEFLAGS) -o $@ $(LIBFLAGS)
	
SOURCES1 = $(SOURCEDIR)libgcm/meshes/tetrahedron/TetrMeshFirstOrder.cpp\
			$(SOURCEDIR)libgcm/meshes/tetrahedron/TetrahedronMesh.cpp\
			$(SOURCEDIR)libgcm/meshes/Mesh.cpp\
			$(SOURCEDIR)libgcm/nodes/CalcNode.cpp\
			$(SOURCEDIR)libgcm/elements/TriangleFirstOrder.cpp\
          	$(SOURCEDIR)libgcm/meshes/tetrahedron/TetrahedronMeshLoader.cpp\
          	$(SOURCEDIR)libgcm/meshes/tetrahedron/MshTetrFileReader.cpp\
          	$(SOURCEDIR)libgcm/snapshotters/VTK2SnapshotWriter.cpp\
          	$(SOURCEDIR)libgcm/snapshotters/SnapshotWriter.cpp\
          	$(SOURCEDIR)libgcm/meshes/partitioners/MetisPartitioner.cpp\
          	$(SOURCEDIR)libgcm/Engine.cpp\
          GmshTest.cpp
OBJECTS1 = $(SOURCES1:%.cpp=%.o)

GmshTest: $(OBJECTS1) 
	$(CPP) $(OBJECTS1) --std=c++11 -I$(INCLUDEDIR) $(INCLUDEFLAGS) -o $@ $(LIBFLAGS)

clean:
	rm -f $(OBJECTS)
	rm -f $(OBJECTS1)
	rm -f RightHandSideSetterTest
	rm -f DispatcherTest