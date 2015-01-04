#ifndef NODE_HPP
#define	NODE_HPP

#include <assert.h>

class Node {
public:
	
	double *vectorInPDE;
	double *valuesInODEs;
	double coords[3];
	unsigned char sizeOfVectorInPDE;
	unsigned char sizeOfValuesInODEs;
	
	Node(unsigned char _sizeOfVectorInPDE, unsigned char _sizeOfValuesInODEs);
	void initMemory(double *buffer, int nodeNum);
	// TODO@avasyukov: implement it correctly
	//Node(const Node &orig);
	~Node();
	void operator=(const Node& orig);
	
private:

};


class NodeWrapper
{
protected:
	Node* baseNode;
	Node* node;
	unsigned int nodesNumber;
	unsigned char TYPE;
	
public:
	
	static const unsigned char GENERIC_WRAPPER_TYPE = 0;
	
	unsigned char getType() {
		return TYPE;
	}
	
	NodeWrapper(Node* baseNode, unsigned int nodesNumber): baseNode(baseNode), nodesNumber(nodesNumber)
	{
		TYPE = GENERIC_WRAPPER_TYPE;
	}
	
	unsigned int getNodesNumber() {
		return nodesNumber;
	}
	
	NodeWrapper& getNode(int number) {
		node = baseNode + number;
		return *this;
	}
	
	NodeWrapper& operator++()
	{
		node++;
	}
	
	double getX()
	{
		return (node->coords)[0];
	}
	
	double getY()
	{
		return (node->coords)[1];
	}
	
	double getZ()
	{
		return (node->coords)[2];
	}
	
	unsigned int getSizeOfVectorInPDE()
	{
		return node->sizeOfVectorInPDE;
	}
	
	unsigned int getSizeOfValuesInODEs()
	{
		return node->sizeOfValuesInODEs;
	}
};


class CalcNodeWrapper: public NodeWrapper
{
	
public:
	static const unsigned char CALC_NODE_WRAPPER_TYPE = 1;
	
	CalcNodeWrapper(Node* node, unsigned int nodesNumber): NodeWrapper(node, nodesNumber)
	{
		assert(node->sizeOfVectorInPDE == 9);
		assert(node->sizeOfValuesInODEs == 0);
		TYPE = CALC_NODE_WRAPPER_TYPE;
	}
	
	double getVx()
	{
		return (node->vectorInPDE)[0];
	}
	
	double getVy()
	{
		return (node->vectorInPDE)[1];
	}
	
	double getVz()
	{
		return (node->vectorInPDE)[2];
	}

	double getFoo()
	{
		return (node->vectorInPDE)[8];
	}
};


class CustomNodeWrapper: public NodeWrapper
{
	
public:
	static const unsigned char CUSTOM_NODE_WRAPPER_TYPE = 2;
	
	CustomNodeWrapper(Node* node, unsigned int nodesNumber): NodeWrapper(node, nodesNumber)
	{
		assert(node->sizeOfVectorInPDE == 11);
		assert(node->sizeOfValuesInODEs == 2);
		TYPE = CUSTOM_NODE_WRAPPER_TYPE;
	}
	
	double getVx()
	{
		return (node->vectorInPDE)[0];
	}
	
	double getVy()
	{
		return (node->vectorInPDE)[1];
	}
	
	double getVz()
	{
		return (node->vectorInPDE)[2];
	}
	
	double getRho()
	{
		return (node->vectorInPDE)[9];
	}
	
	double getTemperature()
	{
		return (node->vectorInPDE)[10];
	}
};

class AnotherCustomNodeWrapper: public NodeWrapper
{
	
public:
	static const unsigned char ANOTHER_CUSTOM_NODE_WRAPPER_TYPE = 3;
	
	AnotherCustomNodeWrapper(Node* node, unsigned int nodesNumber): NodeWrapper(node, nodesNumber)
	{
		assert(node->sizeOfVectorInPDE == 11);
		assert(node->sizeOfValuesInODEs == 5);
		TYPE = ANOTHER_CUSTOM_NODE_WRAPPER_TYPE;
	}
	
	double getVx()
	{
		return (node->vectorInPDE)[0];
	}
	
	double getVy()
	{
		return (node->vectorInPDE)[1];
	}
	
	double getVz()
	{
		return (node->vectorInPDE)[2];
	}
	
	double getRho()
	{
		return (node->vectorInPDE)[9];
	}
	
	double getTemperature()
	{
		return (node->vectorInPDE)[10];
	}
};

#endif	/* NODE_HPP */