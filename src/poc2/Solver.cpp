#include <stdio.h>

#include "Solver.hpp"


void DefaultSolver::doCalc(NodeWrapper& node)
{
	assert(node.getType() == CalcNodeWrapper::CALC_NODE_WRAPPER_TYPE);
	CalcNodeWrapper& cnode = (CalcNodeWrapper&)node;
	// Just test that method exists
	cnode.getFoo();
	printf("DefaultSolver: vector size = %d\n", cnode.getSizeOfVectorInPDE());
}

void CustomSolver::doCalc(NodeWrapper& node)
{
	assert(node.getType() == CustomNodeWrapper::CUSTOM_NODE_WRAPPER_TYPE
		|| node.getType() == AnotherCustomNodeWrapper::ANOTHER_CUSTOM_NODE_WRAPPER_TYPE);
	CustomNodeWrapper& cnode = (CustomNodeWrapper&)node;
	// Just test that method exists
	cnode.getTemperature();
	printf("CustomSolver: vector size = %d\n", cnode.getSizeOfVectorInPDE());
}