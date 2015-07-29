#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <map>
#include <string>
#include <vector>
#include <stdio.h>
#include <mpi.h>

#include "libgcm/util/Singleton.hpp"
#include "libgcm/meshes/cubic/CubicMesh.hpp"
#include "libgcm/meshes/tetrahedron/TetrahedronMesh.hpp"
#include "libgcm/meshes/tetrahedron/TetrMeshFirstOrder.hpp"
#include "libgcm/solvers/FirstOrderSolver.hpp"
#include "libgcm/rheologyModels/models/IdealElasticRheologyModel.hpp"
#include "libgcm/rheologyModels/models/IdealPlasticRheologyModel.hpp"
#include "libgcm/Launcher.hpp"
#include "libgcm/Dispatcher.hpp"
#include "libgcm/Body.hpp"
#include "libgcm/Block.hpp"

namespace gcm {
	class Body;
	class Dispatcher;
	struct Task;
	
	class Engine : public Singleton<Engine>
	{
	protected:
		uint rank;
		uint numberOfWorkers;
		
		real currentTime;
		real requiredTime;
		real fixedTimeStep;

		std::map<std::string, RheologyModel*> rheologyModels;
		std::map<std::string, Solver*> gcmSolvers;

		std::vector<Body*> bodies;

	public:
		Engine();
		~Engine();

		void loadTask(const Task &task);

		// Set fixedTimeStep
		void setTimeStep(real dt);
		// Returns fixedTimeStep
		real getTimeStep();
		
		int getNumberOfWorkers();

		void registerRheologyModel(RheologyModel* model);
		void registerGcmSolver(Solver* solver);
		RheologyModel* getRheologyModel(std::string type) const;
		Solver* getSolver(std::string type) const;

		void calculate();
		void doNextTimeStep();

		// Pattern for name of snapshots
		const static std::string SNAPSHOT_OUTPUT_PATH_PATTERN;

		real getCurrentTime() const;

		void clear();
	};
}

#endif	/* ENGINE_HPP */
