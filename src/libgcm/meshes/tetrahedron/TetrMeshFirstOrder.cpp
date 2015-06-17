#include "libgcm/meshes/tetrahedron/TetrMeshFirstOrder.hpp"

using namespace gcm;

TetrMeshFirstOrder::TetrMeshFirstOrder()
{
}

TetrMeshFirstOrder::~TetrMeshFirstOrder()
{
}

Mesh* TetrMeshFirstOrder::getMeshOfTheSameType() {
	return new TetrMeshFirstOrder();
}

void TetrMeshFirstOrder::checkTopology(float tau)
{
}

int TetrMeshFirstOrder::getTetrsNumber()
{
}

int TetrMeshFirstOrder::getTriangleNumber()
{
}

void TetrMeshFirstOrder::addTetr(TetrahedronFirstOrder& tetr)
{
}

TetrahedronFirstOrder& TetrMeshFirstOrder::getTetr(unsigned int index)
{
}

TetrahedronFirstOrder& TetrMeshFirstOrder::getTetrByLocalIndex(unsigned int index)
{
}

TriangleFirstOrder& TetrMeshFirstOrder::getTriangle(int index)
{
}

bool TetrMeshFirstOrder::hasTetr(unsigned int index)
{
}

void TetrMeshFirstOrder::createTetrs(int number)
{
}

void TetrMeshFirstOrder::createTriangles(int number)
{
}

bool TetrMeshFirstOrder::belongsToTetrahedron(int nodeNum, int tetrNum, int faceNum)
{
}
