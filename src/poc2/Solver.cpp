#include <stdio.h>

#include "Solver.hpp"


void DefaultSolver::doCalc(NodeWrapper* node)
{
	CalcNodeWrapper* cnode = (CalcNodeWrapper*)node;
	// Just test that method exists
	cnode->getFoo();
	printf("DefaultSolver: vector size = %d\n", cnode->getSizeOfVectorInPDE());
}

void CustomSolver::doCalc(NodeWrapper* node)
{
	CustomNodeWrapper* cnode = (CustomNodeWrapper*)node;
	// Just test that method exists
	cnode->getTemperature();
	printf("CustomSolver: vector size = %d\n", cnode->getSizeOfVectorInPDE());
}