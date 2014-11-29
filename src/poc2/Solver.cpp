#include <stdio.h>

#include "Solver.hpp"


void DefaultSolver::doCalc(Node& node)
{
	printf("DefaultSolver: vector size = %d\n", node.sizeOfVectorInPDE);
}

void CustomSolver::doCalc(Node& node)
{
	printf("CustomSolver: vector size = %d\n", node.sizeOfVectorInPDE);
}
