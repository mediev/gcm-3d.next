#include <stdio.h>
#include "mesh.hpp"

void TetrMesh::addNode(CalcNode node)
{
	nodes.push_back(node);
};

CalcNode& TetrMesh::getNode(unsigned int n)
{
	return nodes[n];
};

void CubicMesh::addNode(CalcNode node)
{
	nodes.push_back(node);
};

CalcNode& CubicMesh::getNode(unsigned int n)
{
	return nodes[n];
};

void TetrMesh::load()
{
	for(int i = 0; i < 10; i++)
	{
		CalcNode node;
		nodes.push_back(node);
	}
	printf("TetrMesh loaded: node size = %d\n", getNode(0).VALUES_NUMBER);
};

void CubicMesh::load()
{
	for(int i = 0; i < 10; i++)
	{
		CalcNode node;
		nodes.push_back(node);
	}
	printf("CubicMesh loaded: node size = %d\n", getNode(0).VALUES_NUMBER);
};

void MyCustomTetrMesh::addNode(MyNewCalcNode node)
{
	customNodes.push_back(MyNewCalcNode(node));
};

MyNewCalcNode& MyCustomTetrMesh::getNode(unsigned int n)
{
	return customNodes[n];
};

void MyCustomTetrMesh::load()
{
	for(int i = 0; i < 10; i++)
	{
		MyNewCalcNode node;
		customNodes.push_back(node);
	}
	printf("MyCustomTetrMesh loaded: node size = %d\n", getNode(0).VALUES_NUMBER);
};
