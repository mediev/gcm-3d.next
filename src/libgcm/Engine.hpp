#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <map>
#include <string>
#include <vector>
#include <stdio.h>

#include "libgcm/meshes/cubic/CubicMesh.hpp"
#include "libgcm/meshes/tetrahedron/TetrahedronMesh.hpp"
#include "libgcm/solvers/IdealElasticGcmSolver.hpp"
#include "libgcm/rheologyModels/models/IdealElasticRheologyModel.hpp"
#include "libgcm/Launcher.hpp"
#include "libgcm/Body.hpp"
#include "libgcm/Block.hpp"

namespace gcm {
	class Body;
	struct Task;
	
	class Engine
	{
	protected:
		real currentTime;
		real requiredTime;
		real tau;

		std::map<std::string, RheologyModel*> rheologyModels;
		std::map<std::string, GcmSolver*> GcmSolvers;

		std::vector<Body*> bodies;

	public:
		Engine();
		Engine(const Task &task);
		~Engine();

		void registerRheologyModel(RheologyModel* model);
		void registerGcmSolver(GcmSolver* solver);
		RheologyModel* getRheologyModel(std::string type) const;
		GcmSolver* getSolver(std::string type) const;

		void calculate();
		void doNextTimeStep();

		real getCurrentTime() const;
	};
}

#endif	/* ENGINE_HPP */
