#ifndef SOLVERS
#define SOLVERS 1

#include "nodes.hpp"

class Solver
{
public:
	virtual void doCalc(Node& node) = 0;
};

class DefaultSolver : public Solver
{
public:
	void doCalc(Node& node);
};

class CustomSolver : public Solver
{
public:
	void doCalc(Node& node);
};

#endif
