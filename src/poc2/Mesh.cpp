#include <stdio.h>

#include "Mesh.hpp"

Mesh::Mesh() {
	container = NULL;
}

Mesh::~Mesh() {
	if(container != NULL)
		delete[] container;
}

void Mesh::addNode(CalcNode node) {
	assert(node.TYPE == model->getNodeType());
	assert(node.vectorInPDE != NULL);
	assert(node.valuesInODEs != NULL);
	nodes.push_back(node);
}

CalcNode& Mesh::createNode() {
	unsigned int nodeNum = nodes.size();
	nodes.push_back(newNode(model->getNodeType()));
	nodes[nodeNum].initMemory(container, nodeNum);
	return nodes[nodeNum];
}

CalcNode& Mesh::getNode(unsigned int n) {
	return nodes[n];
}

unsigned int Mesh::getNodesNumber() {
	return nodes.size();
}

//CalcNode& Mesh::getNodes() {
//	return model->castNodes(&nodes[0], nodes.size());
//}

void Mesh::setModel(Model* _model) {
	model = _model;
}

Model *Mesh::getModel() {
	return model;
}

double Mesh::getH() {
	return elem_size;
}

bool Mesh::checkTopology()
{
	// FIXME@mediev: write appropriate code
	return true;
}

double Mesh::getMinH() {
	// FIXME@mediev: write appropriate code
	return elem_size;
}

void Mesh::initContainer(unsigned int numberOfNodes) {
	assert(model != NULL);
	CalcNode tmpNode = newNode(model->getNodeType());
	unsigned char sizeOfValuesInODEs = tmpNode.getSizeOfVectorInPDE();
	unsigned char sizeOfVectorInPDE = tmpNode.getSizeOfValuesInODEs();
	printf("Mesh: init container for %d variables per node (both PDE and ODE)\n", sizeOfValuesInODEs + sizeOfVectorInPDE);
	container = new double[numberOfNodes * (sizeOfValuesInODEs + sizeOfVectorInPDE)];
}

void TetrMesh::load(std::vector<CalcNode>& vertices, unsigned char indx) {
	// We should pre-read number of nodes somehow
	initContainer(NODES_IN_TEST_MESH);
	for(int i = 0; i < NODES_IN_TEST_MESH; i++) {
		CalcNode& newNode = createNode();
		newNode.coords[0] = vertices[indx+i].coords[0];
		newNode.coords[1] = vertices[indx+i].coords[1];
		newNode.coords[2] = vertices[indx+i].coords[2];
	}
	printf("TetrMesh loaded: node size = %d\n", nodes[0].sizeOfVectorInPDE);
}

void CubicMesh::load(std::vector<CalcNode>& vertices, unsigned char indx) {
	// We should pre-read number of nodes somehow
	initContainer(NODES_IN_TEST_MESH);
	for(int i = 0; i < NODES_IN_TEST_MESH; i++) {
		CalcNode& newNode = createNode();
		newNode.coords[0] = vertices[indx+i].coords[0];
		newNode.coords[1] = vertices[indx+i].coords[1];
		newNode.coords[2] = vertices[indx+i].coords[2];
	}
	printf("CubicMesh loaded: node size = %d\n", nodes[0].sizeOfVectorInPDE);
}
