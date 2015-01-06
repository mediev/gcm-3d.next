#include <stdio.h>

#include "Solver.hpp"
#include "Mesh.hpp"

void Solver::calculateMesh(Mesh* mesh) {
	printf("In solver : Model = %s\n", mesh->getModel()->getName());
	unsigned int size = mesh->getNodesNumber();
	for (int i = 0; i < size; i++)
		doCalc(mesh->getNode(i));
}

void DefaultSolver::doCalc(CalcNode& node)
{
	assert(node.getType() == DefaultNode::DEFAULT_NODE_TYPE);
	DefaultNode& cnode = (DefaultNode&)node;
	// Just test that method exists
	cnode.getFoo();
	printf("DefaultSolver: vector size = %d\n", cnode.getSizeOfVectorInPDE());
}

void CustomSolver::doCalc(CalcNode& node)
{
	assert(node.getType() == CustomNode::CUSTOM_NODE_TYPE
		|| node.getType() == AnotherCustomNode::ANOTHER_CUSTOM_NODE_TYPE);
	CustomNode& cnode = (CustomNode&)node;
	// Just test that method exists
	cnode.getTemperature();
	printf("CustomSolver: vector size = %d\n", cnode.getSizeOfVectorInPDE());
}