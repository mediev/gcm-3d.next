#ifndef MESH
#define MESH 1

#include "nodes.hpp"
#include <vector>

template <class NodeType> class Mesh
{
protected:
	std::vector<NodeType> nodes;
public:
	virtual void load() {};
	void addNode(NodeType node);
	NodeType& getNode(unsigned int n);
};

// Derived classes
// Ugly (!) - read http://stackoverflow.com/questions/4010281/accessing-protected-members-of-superclass-in-c-with-templates carefully

template <class NodeType> class TetrMesh : public Mesh<NodeType>
{
using Mesh<NodeType>::nodes;
public:
	void load();
};

template <class NodeType> class CubicMesh : public Mesh<NodeType>
{
using Mesh<NodeType>::nodes;
public:
	void load();
};

#endif
