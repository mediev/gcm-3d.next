#ifndef MESHES_HPP
#define MESHES_HPP 1

#include "nodes.hpp"
#include <iostream>
#include <vector>

template <class NodeType>
class Mesh
{
	protected:
		vector<NodeType> nodes;
	public:
		Mesh();
		virtual ~Mesh();
		
		virtual void load(unsigned int n) {};
		void addNode(NodeType node);
		NodeType& getNode(unsigned int n);
		int nodesNum();
};

template <class NodeType>
class TetrMesh : public Mesh<NodeType>
{
	using Mesh<NodeType>::nodes;
	public:
		void load(unsigned int n);
};

template <class NodeType>
class CubicMesh : public Mesh<NodeType>
{
	using Mesh<NodeType>::nodes;
	public:
		void load(unsigned int n);
};

#endif
