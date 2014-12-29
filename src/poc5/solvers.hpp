#ifndef SOLVERS
#define SOLVERS 1

#include "nodes.hpp"

class Solver
{
public:
	virtual void doCalc(NodeWrapper& node) = 0;
};

class DefaultSolver : public Solver
{
public:
	void doCalc(NodeWrapper1& node)
    {
    }
};

class CustomSolver : public Solver
{
public:
	void doCalc(NodeWrapper2& node) override
    {
    }
};

#endif
