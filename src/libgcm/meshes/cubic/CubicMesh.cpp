#include "libgcm/meshes/cubic/CubicMesh.hpp"

using namespace gcm;

CubicMesh::CubicMesh() {
	type = "CubicMesh";
	movable = false;
}

CubicMesh::CubicMesh(const CubicMesh& orig) {
}

CubicMesh::~CubicMesh() {
}

void CubicMesh::checkTopology(float tau) {
	
}