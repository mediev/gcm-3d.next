#ifndef NODE_HPP
#define	NODE_HPP

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
	const Node* node;
	
public:
	NodeWrapper(const Node* node): node(node)
	{
	}
	
	//TODO: do we really need it?
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
	CalcNodeWrapper(const Node* node): NodeWrapper(node)
	{
		// TODO@avasyukov: assert values size
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
	CustomNodeWrapper(const Node* node): NodeWrapper(node)
	{
		// TODO@avasyukov: assert values size
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