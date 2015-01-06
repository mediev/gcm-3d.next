#ifndef MODEL_HPP
#define	MODEL_HPP

#include "Node.hpp"

class Model {
protected:
	const char *modelName;
public:
	const char *getName();
	virtual unsigned char getSizeOfVectorInPDE() = 0;
	virtual unsigned char getSizeOfValuesInODEs() = 0;
	virtual unsigned char getNodeType() = 0;
};


class ModelOne : public Model {
	static const unsigned char sizeOfVectorInPDE = 9;
	static const unsigned char sizeOfValuesInODEs = 0;
public:
	ModelOne();
	unsigned char getSizeOfVectorInPDE() {return sizeOfVectorInPDE;};
	unsigned char getSizeOfValuesInODEs() {return sizeOfValuesInODEs;};
	unsigned char getNodeType() {return DefaultNode::DEFAULT_NODE_TYPE;};
};

class ModelTwo : public Model {
	static const unsigned char sizeOfVectorInPDE = 11;
	static const unsigned char sizeOfValuesInODEs = 2;
public:
	ModelTwo();
	unsigned char getSizeOfVectorInPDE() {return sizeOfVectorInPDE;};
	unsigned char getSizeOfValuesInODEs() {return sizeOfValuesInODEs;};
	unsigned char getNodeType() {return CustomNode::CUSTOM_NODE_TYPE;};
};

class ModelThree : public Model {
	static const unsigned char sizeOfVectorInPDE = 11;
	static const unsigned char sizeOfValuesInODEs = 5;
public:
	ModelThree();
	unsigned char getSizeOfVectorInPDE() {return sizeOfVectorInPDE;};
	unsigned char getSizeOfValuesInODEs() {return sizeOfValuesInODEs;};
	unsigned char getNodeType() {return AnotherCustomNode::ANOTHER_CUSTOM_NODE_TYPE;};
};

#endif	/* MODEL_HPP */