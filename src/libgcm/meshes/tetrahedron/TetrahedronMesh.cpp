#include "libgcm/meshes/tetrahedron/TetrahedronMesh.hpp"

using namespace gcm;

TetrahedronMesh::TetrahedronMesh() {
	type = "TetrahedronMesh";
}

TetrahedronMesh::TetrahedronMesh(const TetrahedronMesh& orig) {
}

TetrahedronMesh::~TetrahedronMesh() {
}

void TetrahedronMesh::checkTopology(float tau) {
	
}