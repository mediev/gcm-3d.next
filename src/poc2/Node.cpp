#include "Node.hpp"
#include <iostream>

using namespace std;

Node::Node(unsigned char _sizeOfVectorInPDE, unsigned char _sizeOfValuesInODEs) {
	sizeOfValuesInODEs = _sizeOfValuesInODEs;
	sizeOfVectorInPDE = _sizeOfVectorInPDE; 
	vectorInPDE = new double[sizeOfVectorInPDE];
	valuesInODEs = new double[sizeOfValuesInODEs];
}

Node::Node(const Node& orig) {
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
}


Node::~Node() {
	delete [] vectorInPDE;
	delete [] valuesInODEs;
}

void Node::operator=(const Node& orig) {
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
}