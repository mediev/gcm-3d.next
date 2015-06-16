#include "libgcm/meshes/Mesh.hpp"


using namespace gcm;
using std::vector;
using std::unordered_map;

Mesh::Mesh() {
	valuesInNodes = NULL;
	movable = false;
	nodeStorageSize = 0;
}

Mesh::~Mesh() {
	if(valuesInNodes != NULL)
		delete[] valuesInNodes;
}

void Mesh::preProcess()
{
	calcMinH();
	preProcessGeometry();
	createOutline();
}

void Mesh::createOutline()
{
}

void Mesh::initValuesInNodes(unsigned int numberOfNodes) {
	// TODO: Does we call this function once?
	assert(valuesInNodes == NULL);

	// Preparing
	assert(rheologyModel != NULL);
	CalcNode tmpNode = newNode(rheologyModel->getNodeType());
	uchar sizeOfValuesInODE = tmpNode.getSizeOfValuesInPDE();
	uchar sizeOfValuesInPDE = tmpNode.getSizeOfValuesInODE();
	printf("Mesh: init container for %d variables per node (both PDE and ODE)\n",
	       sizeOfValuesInODE + sizeOfValuesInPDE);

	// Allocating
	valuesInNodes = new real[numberOfNodes * (sizeOfValuesInODE + sizeOfValuesInPDE)];
	nodes.reserve(numberOfNodes);
	nodesMap.reserve(numberOfNodes);

	nodeStorageSize = numberOfNodes;
}

void Mesh::addNode(const CalcNode& node)
{
	int nodesNum = nodes.size();
	// TODO: What if we need more memory than we reserved
	assert(nodesNum < nodeStorageSize);

	nodes.push_back(node);
	nodes[nodesNum].initMemory(valuesInNodes, nodesNum);
	nodesMap[node.number] = nodesNum;
}

CalcNode& Mesh::getNode(int index)
{
	assert(index >= 0);
	MapIter itr;
	itr = nodesMap.find(index);
	assert(itr != nodesMap.end());
	return nodes[itr->second];
}

CalcNode& Mesh::getNodeByLocalIndex(uint index)
{
	assert(index >= 0);
	assert(index < nodes.size());
	return nodes[index];
}

int Mesh::getNodeLocalIndex(int index) const
{
	assert(index >= 0);
	MapIter itr;
	itr = nodesMap.find(index);
	assert(itr != nodesMap.end());
	return itr->second;
}

int Mesh::getNodesNumber()
{
	return nodes.size();
}

void Mesh::setRheologyModel(RheologyModel* _rheologyModel) {
	rheologyModel = _rheologyModel;
}

RheologyModel* Mesh::getRheologyModel() {
	return rheologyModel;
}

std::string Mesh::getType() {
	return type;
}
