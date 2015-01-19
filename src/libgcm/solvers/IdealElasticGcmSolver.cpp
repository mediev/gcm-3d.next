#include "IdealElasticGcmSolver.hpp"

using namespace gcm;


IdealElasticGcmSolver::IdealElasticGcmSolver() {
	type = "IdealElasticGcmSolver";
}

IdealElasticGcmSolver::~IdealElasticGcmSolver() {
}

void IdealElasticGcmSolver::doNextTimeStep(Mesh *mesh) {
	std::cout << type << " doNextTimeStep, meshType = " << mesh->getType() << std::endl;
}
