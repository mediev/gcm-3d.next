#include "libgcm/meshes/CubicMesh.hpp"

using namespace gcm;

CubicMesh::CubicMesh() {
	type = "CubicMesh";
}

CubicMesh::CubicMesh(const CubicMesh& orig) {
}

CubicMesh::~CubicMesh() {
}

void CubicMesh::checkTopology(float tau) {
	
}

void CubicMesh::load(std::vector<CalcNode>& vertices, unsigned char indx) {
	// We should pre-read number of nodes somehow
	initValuesInNodes(NODES_IN_TEST_MESH);
	for(int i = 0; i < NODES_IN_TEST_MESH; i++) {
		CalcNode& newNode = createNode();
		newNode.coords[0] = vertices[indx+i].coords[0];
		newNode.coords[1] = vertices[indx+i].coords[1];
		newNode.coords[2] = vertices[indx+i].coords[2];
	}
	printf("CubicMesh loaded\n");
}
