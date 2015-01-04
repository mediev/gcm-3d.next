#ifndef MODEL_HPP
#define	MODEL_HPP

#include "Node.hpp"

class Model {
public:
	virtual unsigned char getSizeOfVectorInPDE() = 0;
	virtual unsigned char getSizeOfValuesInODEs() = 0;
	virtual NodeWrapper& getNodeWrapper(Node* container, unsigned int size) = 0;
};


class ModelOne : public Model {
	static const unsigned char sizeOfVectorInPDE = 9;
	static const unsigned char sizeOfValuesInODEs = 0;
	CalcNodeWrapper* nodeWrapper;
public:
	ModelOne();
	unsigned char getSizeOfVectorInPDE() {return sizeOfVectorInPDE;};
	unsigned char getSizeOfValuesInODEs() {return sizeOfValuesInODEs;};
	NodeWrapper& getNodeWrapper(Node* container, unsigned int size) {
		nodeWrapper = new CalcNodeWrapper(container, size);
		return *nodeWrapper;
	}
};

class ModelTwo : public Model {
	static const unsigned char sizeOfVectorInPDE = 11;
	static const unsigned char sizeOfValuesInODEs = 2;
	CustomNodeWrapper* nodeWrapper;
public:
	ModelTwo();
	unsigned char getSizeOfVectorInPDE() {return sizeOfVectorInPDE;};
	unsigned char getSizeOfValuesInODEs() {return sizeOfValuesInODEs;};
	NodeWrapper& getNodeWrapper(Node* container, unsigned int size) {
		nodeWrapper = new CustomNodeWrapper(container, size);
		return *nodeWrapper;
	}
};

class ModelThree : public Model {
	static const unsigned char sizeOfVectorInPDE = 11;
	static const unsigned char sizeOfValuesInODEs = 5;
	AnotherCustomNodeWrapper* nodeWrapper;
public:
	ModelThree();
	unsigned char getSizeOfVectorInPDE() {return sizeOfVectorInPDE;};
	unsigned char getSizeOfValuesInODEs() {return sizeOfValuesInODEs;};
	NodeWrapper& getNodeWrapper(Node* container, unsigned int size) {
		nodeWrapper = new AnotherCustomNodeWrapper(container, size);
		return *nodeWrapper;
	}
};

#endif	/* MODEL_HPP */