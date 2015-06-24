#include "libgcm/meshes/cubic/CubicMesh.hpp"
#include "libgcm/snapshotters/VTKCubicSnapshotWriter.hpp"

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
	Cube &cube = static_cast<Cube &> (element);
	for (int i = 0; i < 8; i++)
		addNodeIfIsntAlreadyStored(mesh->getNode(cube.vertices[i]));
}

void CubicMesh::sortCubesInGlobalOrder() {
	std::sort(cubes.begin(), cubes.end());
}

void CubicMesh::preProcessGeometry()
{
	// TODO: Finish the function
    /*for(int i = 0; i < getNodesNumber(); i++)
    {
        CalcNode& node = getNodeByLocalIndex(i);
        for( int i = 0; i < 3; i ++)
        {
            if( ( fabs(node.coords[i] - outline.min_coords[i]) < EQUALITY_TOLERANCE )
                || ( fabs(node.coords[i] - outline.max_coords[i]) < EQUALITY_TOLERANCE ) )
            {
                node.setBorder(true);
            }
        }
    }*/
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

const SnapshotWriter& CubicMesh::getSnaphotter() const
{
    return VTKCubicSnapshotWriter::getInstance();
}
