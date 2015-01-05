#include <stdio.h>

#include "Solver.hpp"


void DefaultSolver::doCalc(CalcNode& node)
{
	assert(node.getType() == DefaultNode::CALC_NODE_TYPE);
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