#include "libgcm/meshes/cubic/CubicMesh.hpp"

using namespace gcm;
using std::numeric_limits;

CubicMesh::CubicMesh() {
	meshH = numeric_limits<real>::infinity();
	type = "CubicMesh";
	movable = false;
	cubeLocalIndexToStartCheckingInHasPointFunction = 0;
}

CubicMesh::~CubicMesh() {
	nodes.clear();
}

void CubicMesh::initElements(uint numberOfElements) {
	cubes.reserve(numberOfElements);
}

Mesh* CubicMesh::getMeshOfTheSameType() {
	return new CubicMesh();
}

Element& CubicMesh::getElementByLocalIndex(uint index) {
	return cubes[index];
}

uint CubicMesh::getElementsNumber() {
	return cubes.size();
}

void CubicMesh::addElement(Element& element) {
	cubes.push_back(static_cast<Cube &> (element));
}

vector3r CubicMesh::getCenterOfElement(uint index) {
	Cube &cube = static_cast<Cube &> (getElementByLocalIndex(index));
	return (  getNode(cube.vertices[0]).coords
	        + getNode(cube.vertices[7]).coords ) / 2;
}

void CubicMesh::addElementWithNodes(Element& element, Mesh* mesh) {
	addElement(element);
	Cube &cube = static_cast<Cube&>(element);
	for (int i = 0; i < 8; i++) {
		if( !hasNode(cube.vertices[i]) )
			addNodeWithoutValues(mesh->getNode(cube.vertices[i]));
	}
}

void CubicMesh::sortCubesInGlobalOrder() {
	std::sort(cubes.begin(), cubes.end());
}

void CubicMesh::preProcessGeometry() {
	
	// build border
	std::cout << outline << std::endl;
	for(uint i = 0; i < nodes.size(); i++) {
		CalcNode& node = nodes[i];
		if(  ( fabs(node.coords.x - outline.maxX) < EQUALITY_TOLERANCE * getMinH() ) ||
			 ( fabs(node.coords.x - outline.minX) < EQUALITY_TOLERANCE * getMinH() ) ||
			 ( fabs(node.coords.y - outline.maxY) < EQUALITY_TOLERANCE * getMinH() ) ||
			 ( fabs(node.coords.y - outline.minY) < EQUALITY_TOLERANCE * getMinH() ) ||
			 ( fabs(node.coords.z - outline.maxZ) < EQUALITY_TOLERANCE * getMinH() ) ||
			 ( fabs(node.coords.z - outline.minZ) < EQUALITY_TOLERANCE * getMinH() )  )
			{ node.setBorder(true); newNodes[i].setBorder(true); }
		else
			{ node.setBorder(false); newNodes[i].setBorder(false); }
		}
}

void CubicMesh::calcMinH()
{
	meshH = fabs(getNodeByLocalIndex(0).coords[0] - getNodeByLocalIndex(1).coords[0]);
};

real CubicMesh::getMinH()
{
    if( isinf( meshH ) )
        calcMinH();
    return meshH;
};

bool CubicMesh::hasPoint(const vector3r& r) {
	for(uint i = cubeLocalIndexToStartCheckingInHasPointFunction;
	                                                   i < cubes.size(); i++)
		if ( cubeToAABB(cubes[i]).isInAABB(r) ) {
			cubeLocalIndexToStartCheckingInHasPointFunction = i;
			return true;
		}
	for(uint i = 0; i < cubeLocalIndexToStartCheckingInHasPointFunction; i++)
		if ( cubeToAABB(cubes[i]).isInAABB(r) ) {
			cubeLocalIndexToStartCheckingInHasPointFunction = i;
			return true;
		}
	
	return false;
}

AABB CubicMesh::cubeToAABB(const Cube &cube) {
	CalcNode &minNode = getNode(cube.vertices[0]);
	CalcNode &maxNode = getNode(cube.vertices[7]);
	return AABB(minNode.coords.x, maxNode.coords.x,
	            minNode.coords.y, maxNode.coords.y,
	            minNode.coords.z, maxNode.coords.z);
}

void CubicMesh::checkTopology(float tau) {
}

const SnapshotWriter& CubicMesh::getSnapshotter() const
{
    return VTKCubicSnapshotWriter::getInstance();
}
