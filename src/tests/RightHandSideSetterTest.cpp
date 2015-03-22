#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "libgcm/rheologyModels/rightHandSideSetters/MaxwellViscosityRightHandSideSetter.hpp"
#include "libgcm/solvers/rightHandSideSolvers/FirstOrderRightHandSideSolver.hpp"
#include "libgcm/solvers/rightHandSideSolvers/SecondOrderRightHandSideSolver.hpp"
#include "libgcm/nodes/IdealElasticNode.hpp"
#include "libgcm/nodes/CalcNode.hpp"


using namespace gcm;
using namespace std;

class RightHandSideTest {
public:
	RightHandSideSolver &solver;
	RightHandSideSetter &setter;
	real *container;
	const int numOfTimeSteps = 100;
	const int numOfConvergenceIterations = 10;
	const real rangeToRelaxationTime = 0.1; // the step of integration is 
	                                        // relaxationTime * rangeToRelaxationTime
	vector<double> *solutions;

	const int numberOfNodes = 3;
	IdealElasticNode curNode;
	IdealElasticNode newNode; 
	IdealElasticNode f; // represent right-hand side in "du/dt = f(u,t)"
	
	RightHandSideTest(RightHandSideSolver &solver,
	                  RightHandSideSetter &setter) :
                      solver(solver), setter(setter) {
		solutions = new vector<double> [numOfConvergenceIterations];
		for(int i = 0; i < numOfConvergenceIterations; i++)
			solutions[i].reserve(numOfTimeSteps * (i + 1) + 1);
	};
	
	~RightHandSideTest() {
		delete [] solutions;
	};
					  
	void initNodes() {
		unsigned char sizeOfValuesInPDE = curNode.getSizeOfValuesInPDE();
		unsigned char sizeOfValuesInODE = curNode.getSizeOfValuesInODE();
		container = new real[numberOfNodes * 
		                     (sizeOfValuesInODE + sizeOfValuesInPDE)];
		curNode.initMemory(container, 0);
		newNode.initMemory(container, 1);
		f.initMemory(container, 2);
		for (int i = 0; i < curNode.getSizeOfValuesInPDE(); i++) {
			curNode.valuesInPDE[i] = 1;
			newNode.valuesInPDE[i] = 0;
			f.valuesInPDE[i] = 0;
		}
		for (int i = 0; i < curNode.getSizeOfValuesInODE(); i++) {
			curNode.valuesInODE[i] = 0;
			newNode.valuesInODE[i] = 0;
			f.valuesInODE[i] = 0;
		}
	};

	void calculateExample(real tMax, real tau, vector<double> &solution) {
		initNodes();

		solution.push_back(curNode.getSxx());
		real t = 0;
		while (t < tMax) {
			solver.solve(curNode, newNode, f, tau, setter);
			curNode = newNode;
			t += tau;
			solution.push_back(curNode.getSxx());
		}

		delete [] container;
	};

	void checkConvergence() {
		real tau = rangeToRelaxationTime * 1; // TODO relaxationTime
		real tMax = numOfTimeSteps * tau;
		for (int i = 0; i < numOfConvergenceIterations; i++) {
			calculateExample(tMax, tau, solutions[i]);
			tau /= 2;
		}
		
		// Write file for plotting solutions with different size of steps
		tau = rangeToRelaxationTime * 1; // TODO relaxationTime
		ofstream results;
		results.open("results_of_RightHandSideSetterTest");
		for(int j = 0; j < numOfTimeSteps + 1; j++) {
			results << j*tau << "\t";
			for(int i = 0; i < numOfConvergenceIterations; i++) 
				results << solutions[i][j * pow(2, i)] << "\t";
			results << "\n";
		}
		results.close();
		
		// Check convergence of solutions with different size of steps
		double error[numOfConvergenceIterations - 1];
		cout << "steps are twice reduced every time. errors:\n";
		for(int i = 0; i < numOfConvergenceIterations - 1; i++) {
			error[i] = 0;
			for(unsigned int j = 0; j < solutions[0].size(); j++) {
				double diff = solutions[i][j * pow(2, i)] - solutions[i+1][j * pow(2, i+1)];
				error[i] += diff*diff;
			}
			error[i] = sqrt(error[i]);
			cout << scientific << error[i] << "\t";
		}
		cout << "\nrelation to the next:\n";
		for(int i = 0; i < numOfConvergenceIterations - 2; i++) {
			cout << scientific << error[i]/error[i+1] << "\t";
		}
		cout << endl;
	};
};

void testMaxwellFirstOrder() {
	cout << "\n=== testMaxwellFirstOrder ===\n";
	FirstOrderRightHandSideSolver solver;
	MaxwellViscosityRightHandSideSetter setter;
	RightHandSideTest test = RightHandSideTest(solver, setter);
	test.checkConvergence();
};

void testMaxwellSecondOrder() {
	cout << "\n=== testMaxwellSecondOrder ===\n";
	SecondOrderRightHandSideSolver solver;
	MaxwellViscosityRightHandSideSetter setter;
	RightHandSideTest test = RightHandSideTest(solver, setter);
	test.checkConvergence();
};

int main()
{
	testMaxwellFirstOrder();
	testMaxwellSecondOrder();

    return 0;
}