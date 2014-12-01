#include "block.hpp"
#include <iostream>

template <class NodeType, template <class NodeType> class MeshType>
Block<NodeType, MeshType>::Block()
{
	cout << "Block: creating without any parameters" << endl;
};

template <class NodeType, template <class NodeType> class MeshType>
Block<NodeType, MeshType>::~Block()
{
};

template class Block<FirstNode, CubicMesh>;
template class Block<FirstNode, TetrMesh>;
template class Block<SecondNode, CubicMesh>;
template class Block<SecondNode, TetrMesh>;
template class Block<ThirdNode, CubicMesh>;
template class Block<ThirdNode, TetrMesh>;
