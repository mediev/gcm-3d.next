#include "solvers.hpp"

template <class NodeType>
void CustomSolver<NodeType>::doCalc(NodeType& node)
{
	cout << "CustomSolver: performing calculations" << endl;
};

template <class NodeType>
void DefaultSolver<NodeType>::doCalc(NodeType& node)
{
	cout << "DefaultSolver: performing calculations" << endl;	
};

void DefaultSolver<ThirdNode>::doCalc(ThirdNode& node)
{
	cout << "DefaultSolver: performing calculations" << endl;
};

template class Solver<FirstNode>;
template class Solver<SecondNode>;
template class Solver<ThirdNode>;
template class CustomSolver<FirstNode>;
template class CustomSolver<SecondNode>;
template class CustomSolver<ThirdNode>;
template class DefaultSolver<FirstNode>;
template class DefaultSolver<SecondNode>;
template class DefaultSolver<ThirdNode>;
