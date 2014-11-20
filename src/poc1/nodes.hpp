#ifndef NODES
#define NODES 1

// Base class
class Node
{
public:
};

// Default calc node
class CalcNode : public Node
{
public:
	static int VALUES_NUMBER;
	float values[10];
};

// Completely custom calc node
class MyNewCalcNode : public Node
{
public:
	static int VALUES_NUMBER;
	float values[21];
};

#endif
