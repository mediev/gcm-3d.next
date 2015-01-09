#ifndef SOLVER_HPP
#define	SOLVER_HPP

#include <stdio.h>
#include "Mesh.hpp"

class Solver
{
public:
	void calculateMesh(Mesh *mesh);
	virtual void doCalc(CalcNode& node) = 0;
	virtual std::string getType() = 0;
};

class DefaultSolver : public Solver
{
public:
	void doCalc(CalcNode& node) override;
	std::string getType() override;
};

class CustomSolver : public Solver
{
public:
	void doCalc(CalcNode& node) override;
	std::string getType() override;
};

#endif	/* SOLVER_HPP */
