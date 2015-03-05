#ifndef IDEAL_ELASTIC_GCM_SOLVER_HPP
#define	IDEAL_ELASTIC_GCM_SOLVER_HPP

#include "libgcm/solvers/GcmSolver.hpp"

namespace gcm {
	class IdealElasticGcmSolver : public GcmSolver
	{
	public:
		IdealElasticGcmSolver();
		~IdealElasticGcmSolver();
		void doNextTimeStep(Mesh *mesh) override;

	};
}
#endif	/* IDEAL_ELASTIC_GCM_SOLVER_HPP */

