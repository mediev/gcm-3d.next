#include <stdio.h>

#include "Mesh.hpp"

#define NODES_IN_TEST_MESH 3

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

void Mesh::initContainer(unsigned int numberOfNodes) {
	assert(model != NULL);
	CalcNode tmpNode = newNode(model->getNodeType());
	unsigned char sizeOfValuesInODEs = tmpNode.getSizeOfVectorInPDE();
	unsigned char sizeOfVectorInPDE = tmpNode.getSizeOfValuesInODEs();
	printf("Mesh: init container for %d variables per node (both PDE and ODE)\n", sizeOfValuesInODEs + sizeOfVectorInPDE);
	container = new double[numberOfNodes * (sizeOfValuesInODEs + sizeOfVectorInPDE)];
}

void TetrMesh::load() {
	// We should pre-read number of nodes somehow
	initContainer(NODES_IN_TEST_MESH);
	for(int i = 0; i < NODES_IN_TEST_MESH; i++) {
		CalcNode& newNode = createNode();
		//Fill node
	}
	printf("TetrMesh loaded: node size = %d\n", nodes[0].sizeOfVectorInPDE);
}

void CubicMesh::load() {
	// We should pre-read number of nodes somehow
	initContainer(NODES_IN_TEST_MESH);
	for(int i = 0; i < NODES_IN_TEST_MESH; i++) {
		CalcNode& newNode = createNode();
		//Fill node
	}
	printf("CubicMesh loaded: node size = %d\n", nodes[0].sizeOfVectorInPDE);
}