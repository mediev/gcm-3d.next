#include "libgcm/meshes/tetrahedron/Mesh2GeoLoader.hpp"

using namespace gcm;
using std::string;
using std::to_string;
using std::fstream;
using std::endl;

Mesh2GeoLoader::Mesh2GeoLoader()
{
}

Mesh2GeoLoader::~Mesh2GeoLoader()
{
}

string Mesh2GeoLoader::generateGeoFile(TetrMeshFirstOrder* mesh)
{
	string fileName = "mesh_" + to_string(mesh->getId()) + ".geo";
	fstream geoFile(fileName, std::ios::out);

	real tetrSize = mesh->getMinH();

	geoFile << "$MeshFormat" << endl;

	geoFile.close();

	return fileName;
}

