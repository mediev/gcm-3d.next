#ifndef MODEL_HPP
#define	MODEL_HPP

#include "Node.hpp"

class Model {
public:
	virtual unsigned char getSizeOfVectorInPDE() = 0;
	virtual unsigned char getSizeOfValuesInODEs() = 0;
	virtual CalcNode& castNodes(RawNode* container, unsigned int size) = 0;
};


class ModelOne : public Model {
	static const unsigned char sizeOfVectorInPDE = 9;
	static const unsigned char sizeOfValuesInODEs = 0;
	DefaultNode* nodes;
public:
	ModelOne();
	unsigned char getSizeOfVectorInPDE() {return sizeOfVectorInPDE;};
	unsigned char getSizeOfValuesInODEs() {return sizeOfValuesInODEs;};
	CalcNode& castNodes(RawNode* container, unsigned int size) {
		nodes = new DefaultNode(container, size);
		return *nodes;
	}
};

class ModelTwo : public Model {
	static const unsigned char sizeOfVectorInPDE = 11;
	static const unsigned char sizeOfValuesInODEs = 2;
	CustomNode* nodes;
public:
	ModelTwo();
	unsigned char getSizeOfVectorInPDE() {return sizeOfVectorInPDE;};
	unsigned char getSizeOfValuesInODEs() {return sizeOfValuesInODEs;};
	CalcNode& castNodes(RawNode* container, unsigned int size) {
		nodes = new CustomNode(container, size);
		return *nodes;
	}
};

class ModelThree : public Model {
	static const unsigned char sizeOfVectorInPDE = 11;
	static const unsigned char sizeOfValuesInODEs = 5;
	AnotherCustomNode* nodes;
public:
	ModelThree();
	unsigned char getSizeOfVectorInPDE() {return sizeOfVectorInPDE;};
	unsigned char getSizeOfValuesInODEs() {return sizeOfValuesInODEs;};
	CalcNode& castNodes(RawNode* container, unsigned int size) {
		nodes = new AnotherCustomNode(container, size);
		return *nodes;
	}
};

#endif	/* MODEL_HPP */