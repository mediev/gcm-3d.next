#ifndef NODE_HPP
#define	NODE_HPP

#include <assert.h>

class RawNode {
public:
	
	double *vectorInPDE;
	double *valuesInODEs;
	double coords[3];
	unsigned char sizeOfVectorInPDE;
	unsigned char sizeOfValuesInODEs;
	
	RawNode(unsigned char _sizeOfVectorInPDE, unsigned char _sizeOfValuesInODEs);
	void initMemory(double *buffer, int nodeNum);
	// TODO@avasyukov: implement it correctly
	//Node(const Node &orig);
	~RawNode();
	void operator=(const RawNode& orig);
	
private:

};


class CalcNode
{
protected:
	RawNode* baseNode;
	RawNode* node;
	unsigned int nodesNumber;
	unsigned char TYPE;
	
public:
	
	static const unsigned char GENERIC_NODE_TYPE = 0;
	
	unsigned char getType() {
		return TYPE;
	}
	
	CalcNode(RawNode* baseNode, unsigned int nodesNumber): baseNode(baseNode), nodesNumber(nodesNumber)
	{
		TYPE = GENERIC_NODE_TYPE;
	}
	
	unsigned int getNodesNumber() {
		return nodesNumber;
	}
	
	CalcNode& getNode(int number) {
		node = baseNode + number;
		return *this;
	}
	
	CalcNode& operator++()
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


class DefaultNode: public CalcNode
{
	
public:
	static const unsigned char CALC_NODE_TYPE = 1;
	
	DefaultNode(RawNode* node, unsigned int nodesNumber): CalcNode(node, nodesNumber)
	{
		assert(node->sizeOfVectorInPDE == 9);
		assert(node->sizeOfValuesInODEs == 0);
		TYPE = CALC_NODE_TYPE;
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


class CustomNode: public CalcNode
{
	
public:
	static const unsigned char CUSTOM_NODE_TYPE = 2;
	
	CustomNode(RawNode* node, unsigned int nodesNumber): CalcNode(node, nodesNumber)
	{
		assert(node->sizeOfVectorInPDE == 11);
		assert(node->sizeOfValuesInODEs == 2);
		TYPE = CUSTOM_NODE_TYPE;
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

class AnotherCustomNode: public CalcNode
{
	
public:
	static const unsigned char ANOTHER_CUSTOM_NODE_TYPE = 3;
	
	AnotherCustomNode(RawNode* node, unsigned int nodesNumber): CalcNode(node, nodesNumber)
	{
		assert(node->sizeOfVectorInPDE == 11);
		assert(node->sizeOfValuesInODEs == 5);
		TYPE = ANOTHER_CUSTOM_NODE_TYPE;
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