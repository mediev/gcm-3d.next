#include "Node.hpp"
#include <iostream>

using namespace std;

CalcNode::CalcNode(unsigned char _sizeOfVectorInPDE, unsigned char _sizeOfValuesInODEs, unsigned char _type) {
	TYPE = _type;
	sizeOfValuesInODEs = _sizeOfValuesInODEs;
	sizeOfVectorInPDE = _sizeOfVectorInPDE; 
	vectorInPDE = NULL;
	valuesInODEs = NULL;
}

void CalcNode::initMemory(double *buffer, int nodeNum) {
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


CalcNode::~CalcNode() {
	// No delete[] calls here, since we use placement new 
}

void CalcNode::operator=(const CalcNode& orig) {
	assert(TYPE == orig.TYPE);
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

CalcNode newNode(unsigned char nodeType)
{
	switch (nodeType)
	{
		case DefaultNode::DEFAULT_NODE_TYPE:
			return DefaultNode();
		case CustomNode::CUSTOM_NODE_TYPE:
			return CustomNode();
		case AnotherCustomNode::ANOTHER_CUSTOM_NODE_TYPE:
			return AnotherCustomNode();
	}
			
}