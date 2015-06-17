#include "libgcm/meshes/Mesh.hpp"


using namespace gcm;

Mesh::Mesh() {
	valuesInNodes = NULL;
	movable = false;
}

Mesh::~Mesh() {
	if(valuesInNodes != NULL)
		delete[] valuesInNodes;
}

// TODO rename and restructure these four initializing functions

void Mesh::initNodesWithoutValues(unsigned int numberOfNodes) {
	nodes.reserve(numberOfNodes);
}

void Mesh::addNode(const CalcNode& node) {
	nodes.push_back(node);
}

void Mesh::initValuesInNodes(unsigned int numberOfNodes) {
	initNodesWithoutValues(numberOfNodes);
	assert(rheologyModel != NULL);
	CalcNode tmpNode = newNode(rheologyModel->getNodeType());
	uchar sizeOfValuesInODE = tmpNode.getSizeOfValuesInPDE();
	uchar sizeOfValuesInPDE = tmpNode.getSizeOfValuesInODE();
	printf("Mesh: init container for %d variables per node (both PDE and ODE)\n",
	       sizeOfValuesInODE + sizeOfValuesInPDE);
	valuesInNodes = new real[numberOfNodes * (sizeOfValuesInODE + sizeOfValuesInPDE)];
}

CalcNode& Mesh::createNode(const real &x, const real &y, const real &z) {
	unsigned int nodeNum = nodes.size();
	nodes.push_back(newNode(rheologyModel->getNodeType()));
	nodes[nodeNum].initMemory(valuesInNodes, nodeNum);
	nodes[nodeNum].coords[0] = x;
	nodes[nodeNum].coords[1] = y;
	nodes[nodeNum].coords[2] = z;
	return nodes[nodeNum];
}

void Mesh::setRheologyModel(RheologyModel* _rheologyModel) {
	rheologyModel = _rheologyModel;
}

RheologyModel *Mesh::getRheologyModel() {
	return rheologyModel;
}

std::string Mesh::getType() {
	return type;
}

unsigned int Mesh::getNodesNumber() {
	return nodes.size();
}

CalcNode &Mesh::getNodeByLocalIndex(unsigned int index) {
	return nodes[index];
}

