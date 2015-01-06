#ifndef SOLVER_HPP
#define	SOLVER_HPP

#include "Mesh.hpp"

class Solver
{
public:
	void calculateMesh(Mesh *mesh);
	virtual void doCalc(CalcNode& node) = 0;
};

class DefaultSolver : public Solver
{
public:
	void doCalc(CalcNode& node) override;
};

class CustomSolver : public Solver
{
public:
	void doCalc(CalcNode& node) override;
};

#endif	/* SOLVER_HPP */