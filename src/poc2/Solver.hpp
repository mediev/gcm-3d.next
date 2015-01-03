#ifndef SOLVER_HPP
#define	SOLVER_HPP

#include "Node.hpp"

class Solver
{
public:
	virtual void doCalc(NodeWrapper& node) = 0;
};

class DefaultSolver : public Solver
{
public:
	void doCalc(NodeWrapper& node) override;
};

class CustomSolver : public Solver
{
public:
	void doCalc(NodeWrapper& node) override;
};

#endif	/* SOLVER_HPP */