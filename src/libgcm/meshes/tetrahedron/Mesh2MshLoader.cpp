#include "libgcm/meshes/tetrahedron/Mesh2MshLoader.hpp"

using namespace gcm;

using std::string;
using std::to_string;
using std::endl;
using std::fstream;

Mesh2MshLoader::Mesh2MshLoader()
{
}

Mesh2MshLoader::~Mesh2MshLoader()
{
}

string Mesh2MshLoader::generateMshFile(TetrMeshFirstOrder* mesh)
{
	string fileName = "mesh_" + to_string(mesh->getId()) + ".msh";
	fstream mshFile(fileName, std::ios::out);

	// Writing file format information
	mshFile << "$MeshFormat" << endl;
	// Version of file format, file type and size of floating point numbers used in the file
	mshFile << 2.2 << " " << 0 << " " << 8 << endl;
	mshFile << "$EndMeshFormat" << endl;

	// Writing nodes
	uint nodesNum = mesh->getNodesNumber();
	mshFile << "$Nodes" << endl;
	mshFile << nodesNum << endl;
	for(uint i = 0; i < nodesNum; i++)
		mshFile << i+1 << " " \
				<< mesh->getNodeByLocalIndex(i).coords[0] << " " \
				<< mesh->getNodeByLocalIndex(i).coords[1] << " " \
				<< mesh->getNodeByLocalIndex(i).coords[2] << endl;
	mshFile << "$EndNodes" << endl;

	// Writing tetrs
	uint tetrsNum = mesh->getTetrsNumber();
	mshFile << "$Elements" << endl;
	mshFile << tetrsNum << endl;
	for(uint i = 0; i < tetrsNum; i++) {
		TetrahedronFirstOrder& tetr = mesh->getTetrByLocalIndex(i);
		// Number of tetrahedron, number of tags(necessary), two necessary tags, list of nodes composes tetrahgedron
		mshFile << i+1 << " " << 4 << " " << 2 << " " << 0 << " " << 36 << " "  \
				<< mesh->getNodeLocalIndex(tetr.vertices[0]) + 1 << " " \
				<< mesh->getNodeLocalIndex(tetr.vertices[1]) + 1 << " " \
				<< mesh->getNodeLocalIndex(tetr.vertices[2]) + 1 << " " \
				<< mesh->getNodeLocalIndex(tetr.vertices[3]) + 1 << endl;
	}
	mshFile << "$EndElements" << endl;

	mshFile.close();

	return fileName;
}
