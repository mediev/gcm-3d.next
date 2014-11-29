#include <stdio.h>

#include "Mesh.hpp"

Mesh::Mesh() {
}

Mesh::~Mesh() {
}

void Mesh::addNode(Node node) {
	nodes.push_back(node);
}

Node& Mesh::getNode(unsigned int n) {
	return nodes[n];
}

void TetrMesh::load(unsigned char sizeOfVectorInPDE, unsigned char sizeOfValuesInODEs) {
	for(int i = 0; i < 10; i++) {
		nodes.push_back(Node(sizeOfVectorInPDE, sizeOfValuesInODEs));
	}
	printf("TetrMesh loaded: node size = %d\n", nodes[0].sizeOfVectorInPDE);
}

void CubicMesh::load(unsigned char sizeOfVectorInPDE, unsigned char sizeOfValuesInODEs) {
	for(int i = 0; i < 10; i++) {
		nodes.push_back(Node(sizeOfVectorInPDE, sizeOfValuesInODEs));
	}
	printf("CubicMesh loaded: node size = %d\n", nodes[0].sizeOfVectorInPDE);
}
