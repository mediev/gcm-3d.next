#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <map>
#include <string>
#include <vector>
#include <stdio.h>
#include <mpi.h>
#include <limits>

#include "libgcm/util/Singleton.hpp"
#include "libgcm/meshes/cubic/CubicMesh.hpp"
#include "libgcm/meshes/tetr/TetrMesh.hpp"
#include "libgcm/meshes/tetr/TetrMeshFirstOrder.hpp"
#include "libgcm/solvers/FirstOrderSolver.hpp"
#include "libgcm/rheologyModels/models/IdealElasticRheologyModel.hpp"
#include "libgcm/rheologyModels/models/IdealPlasticRheologyModel.hpp"
#include "libgcm/Launcher.hpp"
#include "libgcm/Dispatcher.hpp"
#include "libgcm/Body.hpp"
#include "libgcm/Block.hpp"
#include "libgcm/DataBus.hpp"

namespace gcm {
	class Body;
	class DataBus;
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

		// The entity to transfer data between cores with MPI
		DataBus* dataBus;

	public:
		Engine();
		~Engine();

		void loadTask(const Task &task);

		// Set fixedTimeStep
		void setTimeStep(real dt);
		// Returns fixedTimeStep
		real getTimeStep();

		void registerRheologyModel(RheologyModel* model);
		void registerGcmSolver(Solver* solver);
		RheologyModel* getRheologyModel(std::string type) const;
		Solver* getSolver(std::string type) const;

		void calculate();
		void doNextTimeStep();

		// Pattern for name of snapshots
		const static std::string SNAPSHOT_OUTPUT_PATH_PATTERN;

		// Returns rank of performing core
		uint getRank();
		// Returns number of performing cores
		uint getNumberOfWorkers();
		// Returns pointer to DataBus
		DataBus* getDataBus();

		real getCurrentTime() const;

		void clear();
	};
}

#endif	/* ENGINE_HPP */
