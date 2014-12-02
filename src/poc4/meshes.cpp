#include "meshes.hpp"

template <class NodeType>
Mesh<NodeType>::Mesh()
{
};

template <class NodeType>
Mesh<NodeType>::~Mesh()
{	
};

template <class NodeType>
void Mesh<NodeType>::addNode(NodeType node)
{
	nodes.push_back(node);
};

template <class NodeType>
NodeType& Mesh<NodeType>::getNode(unsigned int n)
{
	return nodes[n];
};

template <class NodeType>
int Mesh<NodeType>::nodesNum()
{
	return nodes.size();
};

template <class NodeType>
void TetrMesh<NodeType>::load(unsigned int n)
{
	for(int i = 0; i < n; i++) {
		NodeType node;
		nodes.push_back(node);
	}
	cout << "TetrMesh: " << n << " nodes loaded" << endl;
};

template <class NodeType>
void CubicMesh<NodeType>::load(unsigned int n)
{
	for(int i = 0; i < n; i++) {
		NodeType node;
		nodes.push_back(node);
	}
	cout << "CubicMesh: " << n << " nodes loaded" << endl;
};

template class Mesh<FirstNode>;
template class Mesh<SecondNode>;
template class Mesh<ThirdNode>;
template class TetrMesh<FirstNode>;
template class TetrMesh<SecondNode>;
template class TetrMesh<ThirdNode>;
template class CubicMesh<FirstNode>;
template class CubicMesh<SecondNode>;
template class CubicMesh<ThirdNode>;
