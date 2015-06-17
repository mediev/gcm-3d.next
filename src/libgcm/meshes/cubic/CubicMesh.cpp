#include "libgcm/meshes/cubic/CubicMesh.hpp"

using namespace gcm;

CubicMesh::CubicMesh() {
	type = "CubicMesh";
	movable = false;
}

CubicMesh::~CubicMesh() {
}

void CubicMesh::checkTopology(float tau) {
	
}

Mesh* CubicMesh::getMeshOfTheSameType() {
	return new CubicMesh();
}
