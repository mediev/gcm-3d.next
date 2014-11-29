#include <stdio.h>
#include "solvers.hpp"

void DefaultSolver::doCalc(Node& _node)
{
	CalcNode& node = (CalcNode&)_node;
	printf("DefaultSolver: node size = %d\n", node.VALUES_NUMBER);
}

void CustomSolver::doCalc(Node& _node)
{
	MyNewCalcNode& node = (MyNewCalcNode&)_node;
	printf("CustomSolver: node size = %d\n", node.VALUES_NUMBER);
}
