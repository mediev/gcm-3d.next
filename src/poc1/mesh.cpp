#include <stdio.h>
#include "mesh.hpp"

template <class NodeType> void Mesh<NodeType>::addNode(NodeType node)
{
	nodes.push_back(node);
};

template <class NodeType> NodeType& Mesh<NodeType>::getNode(unsigned int n)
{
	return nodes[n];
};

template <class NodeType> void TetrMesh<NodeType>::load()
{
	for(int i = 0; i < 10; i++)
	{
		NodeType node;
		nodes.push_back(node);
	}
	printf("TetrMesh loaded: node size = %d\n", nodes[0].VALUES_NUMBER);
};

template <class NodeType> void CubicMesh<NodeType>::load()
{
	for(int i = 0; i < 10; i++)
	{
		NodeType node;
		nodes.push_back(node);
	}
	printf("CubicMesh loaded: node size = %d\n", nodes[0].VALUES_NUMBER);
};

// Ugly (!) - see
//	- http://stackoverflow.com/questions/1724036/splitting-templated-c-classes-into-hpp-cpp-files-is-it-possible
//	- http://stackoverflow.com/questions/8752837/undefined-reference-to-template-class-constructor
template class Mesh<CalcNode>;
template class Mesh<MyNewCalcNode>;
template class TetrMesh<CalcNode>;
template class TetrMesh<MyNewCalcNode>;
template class CubicMesh<CalcNode>;
template class CubicMesh<MyNewCalcNode>;
