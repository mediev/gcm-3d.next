#ifndef BLOCK_HPP
#define BLOCK_HPP 1

#include "meshes.hpp"

template <class NodeType, template <class NodeType> class MeshType>
class Block
{
	public:
		Block();
		Block(MeshType<NodeType>* _mesh) : mesh(_mesh) {};
		~Block();
		
		MeshType<NodeType>* mesh;
};

#endif
