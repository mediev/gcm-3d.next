#ifndef NODE_HPP
#define	NODE_HPP

#include <assert.h>
#include <string>

#define GENERIC_NODE_TYPE 0
#define DEFAULT_NODE_TYPE 1
#define CUSTOM_NODE_TYPE 2
#define ANOTHER_CUSTOM_NODE_TYPE 3

class CalcNode {
	
public:
	//static const unsigned char GENERIC_NODE_TYPE = 0;
	
	unsigned char TYPE;
	double *vectorInPDE;
	double *valuesInODEs;
	double coords[3];
	unsigned char sizeOfVectorInPDE;
	unsigned char sizeOfValuesInODEs;
	
	CalcNode(unsigned char _sizeOfVectorInPDE, unsigned char _sizeOfValuesInODEs, unsigned char _type);
	void initMemory(double *buffer, int nodeNum);
	// TODO@avasyukov: implement it correctly
	//Node(const Node &orig);
	~CalcNode();
	void operator=(const CalcNode& orig);

	void setType(unsigned char type) {
		TYPE = type;
	}
	
	unsigned char getType() {
		return TYPE;
	}

	unsigned int getSizeOfVectorInPDE()
	{
		return sizeOfVectorInPDE;
	}
	
	unsigned int getSizeOfValuesInODEs()
	{
		return sizeOfValuesInODEs;
	}
	
	double getX()
	{
		return coords[0];
	}
	
	double getY()
	{
		return coords[1];
	}
	
	double getZ()
	{
		return coords[2];
	}
};


class DefaultNode: public CalcNode
{
	
public:
	
	//static const unsigned char DEFAULT_NODE_TYPE = 1;

	DefaultNode() : CalcNode(9, 0, DEFAULT_NODE_TYPE)
	{
	}
	
	double getVx()
	{
		return vectorInPDE[0];
	}
	
	double getVy()
	{
		return vectorInPDE[1];
	}
	
	double getVz()
	{
		return vectorInPDE[2];
	}

	double getFoo()
	{
		return vectorInPDE[8];
	}
};


class CustomNode: public CalcNode
{
	
public:
	
	//static const unsigned char CUSTOM_NODE_TYPE = 2;

	CustomNode() : CalcNode(11, 0, CUSTOM_NODE_TYPE)
	{
	}

	double getVx()
	{
		return vectorInPDE[0];
	}
	
	double getVy()
	{
		return vectorInPDE[1];
	}
	
	double getVz()
	{
		return vectorInPDE[2];
	}
	
	double getRho()
	{
		return vectorInPDE[9];
	}
	
	double getTemperature()
	{
		return vectorInPDE[10];
	}
};

class AnotherCustomNode: public CalcNode
{
	
public:
	//static const unsigned char ANOTHER_CUSTOM_NODE_TYPE = 3;

	AnotherCustomNode() : CalcNode(11, 2, ANOTHER_CUSTOM_NODE_TYPE)
	{
	}
	
	double getVx()
	{
		return vectorInPDE[0];
	}
	
	double getVy()
	{
		return vectorInPDE[1];
	}
	
	double getVz()
	{
		return vectorInPDE[2];
	}
	
	double getRho()
	{
		return vectorInPDE[9];
	}
	
	double getTemperature()
	{
		return vectorInPDE[10];
	}
};

CalcNode newNode(unsigned char nodeType);

#endif	/* NODE_HPP */
