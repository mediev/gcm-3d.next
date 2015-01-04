#include "Node.hpp"
#include <iostream>

using namespace std;

Node::Node(unsigned char _sizeOfVectorInPDE, unsigned char _sizeOfValuesInODEs) {
	sizeOfValuesInODEs = _sizeOfValuesInODEs;
	sizeOfVectorInPDE = _sizeOfVectorInPDE; 
	vectorInPDE = NULL;
	valuesInODEs = NULL;
}

void Node::initMemory(double *buffer, int nodeNum) {
	double* startAddr = buffer + nodeNum * (sizeOfVectorInPDE + sizeOfValuesInODEs);
	vectorInPDE = new (startAddr) double[sizeOfVectorInPDE];
	valuesInODEs = new (startAddr + sizeOfVectorInPDE) double[sizeOfValuesInODEs];
}

/*Node::Node(const Node& orig) {
	sizeOfValuesInODEs = orig.sizeOfValuesInODEs;
	sizeOfVectorInPDE = orig.sizeOfVectorInPDE;
	coords[0] = orig.coords[0];
	coords[1] = orig.coords[1];
	coords[2] = orig.coords[2];
	vectorInPDE = new double[sizeOfVectorInPDE];
	valuesInODEs = new double[sizeOfValuesInODEs];
	for (int i = 0; i < sizeOfVectorInPDE; i++)
		vectorInPDE[i] = orig.vectorInPDE[i];
	for (int i = 0; i < sizeOfValuesInODEs; i++)
		valuesInODEs[i] = orig.valuesInODEs[i];
}*/


Node::~Node() {
	// No delete[] calls here, since we use placement new 
}

void Node::operator=(const Node& orig) {
	assert(sizeOfValuesInODEs == orig.sizeOfValuesInODEs);
	assert(sizeOfVectorInPDE = orig.sizeOfVectorInPDE);
	assert(vectorInPDE != NULL);
	assert(valuesInODEs != NULL);
	coords[0] = orig.coords[0];
	coords[1] = orig.coords[1];
	coords[2] = orig.coords[2];
	for (int i = 0; i < sizeOfVectorInPDE; i++)
		vectorInPDE[i] = orig.vectorInPDE[i];
	for (int i = 0; i < sizeOfValuesInODEs; i++)
		valuesInODEs[i] = orig.valuesInODEs[i];
}