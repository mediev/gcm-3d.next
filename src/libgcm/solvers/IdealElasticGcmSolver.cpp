#include "IdealElasticGcmSolver.hpp"

using namespace gcm;


IdealElasticGcmSolver::IdealElasticGcmSolver() {
	type = "IdealElasticGcmSolver";
}

IdealElasticGcmSolver::~IdealElasticGcmSolver() {
}

void IdealElasticGcmSolver::doNextTimeStep(Mesh *mesh) {
	std::cout << "doNextTimeStep. Worker: " << MPI::COMM_WORLD.Get_rank()
	          << " type of solver: " << type 
	          << " meshId: " << mesh->getId()
	          << " meshRank: " << mesh->getRank()
	          << " meshType: " << mesh->getType()
	          << std::endl;
}
