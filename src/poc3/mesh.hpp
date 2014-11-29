#ifndef MESH
#define MESH 1

#include "nodes.hpp"
#include <vector>

class Mesh
{
protected:
	std::vector<CalcNode> nodes;
public:
	virtual void load() {};
	virtual void addNode(CalcNode node) {};
	virtual CalcNode& getNode(unsigned int n) {};
};

class TetrMesh : public Mesh
{
public:
	void addNode(CalcNode node);
	CalcNode& getNode(unsigned int n);
	void load();
};

class CubicMesh : public Mesh
{
public:
	void addNode(CalcNode node);
	CalcNode& getNode(unsigned int n);
	void load();
};

class MyCustomTetrMesh : public Mesh
{
	std::vector<MyNewCalcNode> customNodes;
public:
	void addNode(MyNewCalcNode node);
	MyNewCalcNode& getNode(unsigned int n);
	void load();
};

#endif
