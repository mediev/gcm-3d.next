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

void Mesh::addNode(Node node) {
	assert(node.sizeOfVectorInPDE == model->getSizeOfVectorInPDE());
	assert(node.sizeOfValuesInODEs == model->getSizeOfValuesInODEs());
	assert(node.vectorInPDE != NULL);
	assert(node.valuesInODEs != NULL);
	nodes.push_back(node);
}

Node& Mesh::createNode() {
	unsigned int nodeNum = nodes.size();
	nodes.push_back(Node(model->getSizeOfVectorInPDE(), model->getSizeOfValuesInODEs()));
	nodes[nodeNum].initMemory(container, nodeNum);
	return nodes[nodeNum];
}

Node& Mesh::getNode(unsigned int n) {
	return nodes[n];
}

NodeWrapper& Mesh::getNodeWrapper() {
	return model->getNodeWrapper(&nodes[0], nodes.size());
}

void Mesh::setModel(Model* _model) {
	model = _model;
}

void Mesh::initContainer(unsigned int numberOfNodes) {
	assert(model != NULL);
	unsigned char sizeOfValuesInODEs = model->getSizeOfVectorInPDE();
	unsigned char sizeOfVectorInPDE = model->getSizeOfValuesInODEs();
	container = new double[numberOfNodes * (sizeOfValuesInODEs + sizeOfVectorInPDE)];
}

void TetrMesh::load() {
	// We should pre-read number of nodes somehow
	initContainer(NODES_IN_TEST_MESH);
	for(int i = 0; i < NODES_IN_TEST_MESH; i++) {
		Node& newNode = createNode();
		//Fill node
	}
	printf("TetrMesh loaded: node size = %d\n", nodes[0].sizeOfVectorInPDE);
}

void CubicMesh::load() {
	// We should pre-read number of nodes somehow
	initContainer(NODES_IN_TEST_MESH);
	for(int i = 0; i < NODES_IN_TEST_MESH; i++) {
		Node& newNode = createNode();
		//Fill node
	}
	printf("CubicMesh loaded: node size = %d\n", nodes[0].sizeOfVectorInPDE);
}