#ifndef MODEL_HPP
#define	MODEL_HPP

#include "Node.hpp"

class Model {
public:
	virtual unsigned char getSizeOfVectorInPDE() = 0;
	virtual unsigned char getSizeOfValuesInODEs() = 0;
	virtual NodeWrapper* getNodeWrapper(const Node* container) = 0;
};


class ModelOne : public Model {
	static const unsigned char sizeOfVectorInPDE = 9;
	static const unsigned char sizeOfValuesInODEs = 0;
public:
	ModelOne();
	unsigned char getSizeOfVectorInPDE() {return sizeOfVectorInPDE;};
	unsigned char getSizeOfValuesInODEs() {return sizeOfValuesInODEs;};
	NodeWrapper* getNodeWrapper(const Node* container) {
		return new CalcNodeWrapper(container);
	}
};

class ModelTwo : public Model {
	static const unsigned char sizeOfVectorInPDE = 11;
	static const unsigned char sizeOfValuesInODEs = 2;
public:
	ModelTwo();
	unsigned char getSizeOfVectorInPDE() {return sizeOfVectorInPDE;};
	unsigned char getSizeOfValuesInODEs() {return sizeOfValuesInODEs;};
	NodeWrapper* getNodeWrapper(const Node* container) {
		return new CustomNodeWrapper(container);
	}
};

class ModelThree : public Model {
	static const unsigned char sizeOfVectorInPDE = 11;
	static const unsigned char sizeOfValuesInODEs = 5;
public:
	ModelThree();
	unsigned char getSizeOfVectorInPDE() {return sizeOfVectorInPDE;};
	unsigned char getSizeOfValuesInODEs() {return sizeOfValuesInODEs;};
	NodeWrapper* getNodeWrapper(const Node* container) {
		return new CustomNodeWrapper(container);
	}
};

#endif	/* MODEL_HPP */