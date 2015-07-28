#include "libgcm/meshes/tetrahedron/TetrMeshFirstOrder.hpp"
#include "libgcm/meshes/tetrahedron/TetrahedronMeshLoader.hpp"
#include "libgcm/snapshotters/VTK2SnapshotWriter.hpp"
#include "libgcm/meshes/partitioners/MetisPartitioner.hpp"

#include <gmsh/Gmsh.h>
#include <gmsh/GModel.h>
#include <gmsh/GEntity.h>
#include <gmsh/MElement.h>
#include <gmsh/MVertex.h>
#include <gmsh/MTriangle.h>
#include <gmsh/MTetrahedron.h>

using namespace gcm;
using std::string;
using std::fstream;
using std::to_string;
using std::fill_n;
using std::vector;
using std::find;

void generateGeoFile(TetrMeshFirstOrder* mesh, string geoName, float spatialStep)
{
	fstream geoFile(geoName, std::ios::out);

	geoFile << "meshPointDist = " << spatialStep << ";\n";
	geoFile << "\n";

	int nodesNum = mesh->getNodesNumber();
	int counter = 0;
	for(int i = 0; i < nodesNum; i++) {
		CalcNode& node = mesh->getNodeByLocalIndex(i);
		if( node.isBorder() ) {
			geoFile << "Point(" << i + 1 << ") = {" << node.coords[0] << ", " \
					<< node.coords[1] << ", " \
					<< node.coords[2] << ", " \
					<< spatialStep << "};\n";
			counter = i + 1;
		}
	}
	counter++;

	vector< vector<int> > lines;
	vector<int>::iterator it;

	lines.resize(nodesNum);
	int verts [3];
	int line [3];
	int triNum = mesh->getTriangleNumber();
	int triangles [triNum];
	for(int j = 0; j < triNum; j++) {
		TriangleFirstOrder& tri = mesh->getTriangle(j);
		verts[0] = mesh->getNodeLocalIndex(tri.vertices[0]);
		verts[1] = mesh->getNodeLocalIndex(tri.vertices[1]);
		verts[2] = mesh->getNodeLocalIndex(tri.vertices[2]);
		it = lines[verts[0]].find(verts[1]);
		if(it != lines[verts[0]].end())
			line[0] = *it;
		else
			*it = counter;
		geoFile << "Line(" << counter << ") = {" << mesh->getNodeLocalIndex(tetr.vertices[0])+1 << ", " \\
										   << mesh->

	}

	geoFile.close();
	std::cout << mesh->getNodeByLocalIndex(0).coords << "\n";
}

int main(int argc, char* argv[])
{
	GmshInitialize();

	int nparts = 2;
	float spatialStep = 1.0;
	string geoName;

	Engine& engine = Engine::getInstance();
	RheologyModel* model = engine.getRheologyModel("IdealElasticRheologyModel");

	TetrMeshFirstOrder* coarseMesh = new TetrMeshFirstOrder();
	coarseMesh->setId(100);
	coarseMesh->setRheologyModel(model);

	TetrahedronMeshLoader& loader = TetrahedronMeshLoader::getInstance();
	loader.loadMesh(coarseMesh, "/home/mediev/projects-repo/gcm-3d-mediev/gcm-3d.next/models/cube.geo", spatialStep);

	TetrMeshFirstOrder* coarsePart = new TetrMeshFirstOrder [nparts];
	MetisPartitioner::getInstance().partMesh(coarseMesh, nparts, coarsePart);

	TetrMeshFirstOrder* fineMesh = new TetrMeshFirstOrder [nparts];

	for(int i = 0; i < nparts; i++)
	{
		geoName = "part_" + to_string(i) + ".geo";
		coarsePart[i].preProcess();
		generateGeoFile(&coarsePart[i], geoName, spatialStep / 2.0);
		fineMesh[i].setId(200 + i);
		fineMesh[i].setRheologyModel(model);

		loader.loadMesh(&fineMesh[i], "/home/mediev/projects-repo/gcm-3d-mediev/gcm-3d.next/" + geoName, spatialStep / 2.0);
	}

	GmshFinalize();
	return 0;
}


