#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <map>
#include <string>
#include <vector>
#include <stdio.h>

#include "libgcm/meshes/CubicMesh.hpp"
#include "libgcm/meshes/TetrahedronMesh.hpp"
#include "libgcm/solvers/IdealElasticGcmSolver.hpp"
#include "libgcm/rheologyModels/models/IdealElasticRheologyModel.hpp"
#include "libgcm/Body.hpp"
#include "libgcm/Block.hpp"

namespace gcm {
	class Engine
	{
		protected:
			std::map<std::string, RheologyModel*> rheologyModels;
			std::map<std::string, GcmSolver*> GcmSolvers;
			std::vector<Body*> bodies;

		public:
			Engine();
			~Engine();

			void cleanUp();

			void registerRheologyModel(RheologyModel* model);
			void registerGcmSolver(GcmSolver* solver);

			RheologyModel* getRheologyModel(std::string modelType);
			GcmSolver* getSolver(std::string solverType);

			Body* getBody(unsigned char num);
			void addBody(Body* body);

			void doNextStep();
	};
}

#endif	/* ENGINE_HPP */
