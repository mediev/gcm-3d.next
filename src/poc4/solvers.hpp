#ifndef SOLVERS_HPP
#define SOLVERS_HPP 1

#include "nodes.hpp"

template <class NodeType>
class Solver
{
	public:
		virtual void doCalc(NodeType& node) = 0;
};

template <class NodeType>
class CustomSolver : public Solver<NodeType>
{
	public:	
		void doCalc(NodeType& node);
};

template <class NodeType>
class DefaultSolver : public Solver<NodeType>
{
	public:	
		void doCalc(NodeType& node);
};

// Specification of DefaultSolver class for ThirdNode (for instance)
template <>
class DefaultSolver<ThirdNode> : public Solver<ThirdNode>
{
	public:	
		void doCalc(ThirdNode& node);
};

#endif
