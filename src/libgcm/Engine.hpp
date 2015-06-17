#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <map>
#include <string>
#include <vector>
#include <stdio.h>
#include "mpi.h"

#include "libgcm/util/Singleton.hpp"
#include "libgcm/meshes/cubic/CubicMesh.hpp"
#include "libgcm/meshes/tetrahedron/TetrahedronMesh.hpp"
#include "libgcm/meshes/tetrahedron/TetrMeshFirstOrder.hpp"
#include "libgcm/solvers/IdealElasticGcmSolver.hpp"
#include "libgcm/rheologyModels/models/IdealElasticRheologyModel.hpp"
#include "libgcm/Launcher.hpp"
#include "libgcm/Body.hpp"
#include "libgcm/Block.hpp"

namespace gcm {
	class Body;
	struct Task;
	
	class Engine : public Singleton<Engine>
	{
	protected:
		int rank;
		int numberOfWorkers;
		
		real currentTime;
		real requiredTime;
		real tau;

		std::map<std::string, RheologyModel*> rheologyModels;
		std::map<std::string, GcmSolver*> gcmSolvers;

		std::vector<Body*> bodies;

		real fixedTimeStep;

	public:
		Engine();
		~Engine();

		void loadTask(const Task &task);

		// Set fixedTimeStep
		void setTimeStep(real dt);
		// Returns fixedTimeStep
		real getTimeStep();

		void registerRheologyModel(RheologyModel* model);
		void registerGcmSolver(GcmSolver* solver);
		RheologyModel* getRheologyModel(std::string type) const;
		GcmSolver* getSolver(std::string type) const;

		void calculate();
		void doNextTimeStep();

		real getCurrentTime() const;

		void clear();
	};
}

#endif	/* ENGINE_HPP */
