#ifndef SOLVER_HPP
#define	SOLVER_HPP

#include "Node.hpp"

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

#endif	/* SOLVER_HPP */

