#include <iostream>

#include "libgcm/rheologyModels/rightHandSideSetters/MaxwellViscosityRightHandSideSetter.hpp"
#include "libgcm/solvers/rightHandSideSolvers/FirstOrderRightHandSideSolver.hpp"
#include "libgcm/solvers/rightHandSideSolvers/SecondOrderRightHandSideSolver.hpp"
#include "libgcm/nodes/IdealElasticNode.hpp"
#include "libgcm/nodes/CalcNode.hpp"


using namespace gcm;
using namespace std;

int main()
{
	IdealElasticNode curNode;
	IdealElasticNode newNode;
	IdealElasticNode f; // represent right-hand side in "du/dt = f(u,t)"
	int numberOfNodes = 3;
	unsigned char sizeOfValuesInPDE = curNode.getSizeOfValuesInPDE();
	unsigned char sizeOfValuesInODE = curNode.getSizeOfValuesInODE();
	real *container = new real[numberOfNodes * (sizeOfValuesInODE + sizeOfValuesInPDE)];
	curNode.initMemory(container, 0);
	newNode.initMemory(container, 1);
	f.initMemory(container, 2);
	
	cout << curNode.getSxx() << endl;
	
	
	FirstOrderRightHandSideSolver solver;
	MaxwellViscosityRightHandSideSetter setter;
	real tau = 0.1;
	solver.solve(curNode, newNode, f, tau, setter);

	cout << newNode.getSxx() << endl;

	
	delete [] container;
    return 0;
}