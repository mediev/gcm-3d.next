#include "libgcm/solvers/rightHandSideSolvers/SecondOrderRightHandSideSolver.hpp"

using namespace gcm;

void SecondOrderRightHandSideSolver::solve(const CalcNode& curNode,
                                          CalcNode& newNode, CalcNode& f,
                                          const gcm::real tau, 
                                          const RightHandSideSetter& setter) {
	// second-order "predictor-corrector" formula for ODE
	
	// predictor
	setter.setVector(f, curNode);
	for (int i = 0; i < curNode.getSizeOfValuesInPDE(); i++)
		newNode.valuesInPDE[i] = curNode.valuesInPDE[i]
							   + tau / 2 * f.valuesInPDE[i];
	// corrector
	setter.setVector(f, newNode);
	for (int i = 0; i < curNode.getSizeOfValuesInPDE(); i++)
		newNode.valuesInPDE[i] = curNode.valuesInPDE[i]
							   + tau * f.valuesInPDE[i];
}
