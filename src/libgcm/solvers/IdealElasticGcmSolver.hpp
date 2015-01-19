#ifndef IDEALELASTICGCMSOLVER_HPP
#define	IDEALELASTICGCMSOLVER_HPP

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
#endif	/* IDEALELASTICGCMSOLVER_HPP */

