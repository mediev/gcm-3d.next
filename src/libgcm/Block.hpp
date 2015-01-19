#ifndef BLOCK_HPP
#define	BLOCK_HPP

#include "libgcm/meshes/Mesh.hpp"
#include "libgcm/solvers/GcmSolver.hpp"
#include "libgcm/rheologyModels/models/RheologyModel.hpp"

namespace gcm {
	class Block
	{
		protected:
			std::string name;
			RheologyModel* model;
			GcmSolver* solver;
			Mesh* mesh;
		public:
			Block(Mesh* _mesh) : mesh(_mesh) {};
			Block(std::string _name, RheologyModel* _model, GcmSolver* _solver, Mesh* _mesh) : 
				name(_name), model(_model), solver(_solver), mesh(_mesh) {};

			void doNextTimeStep();
			void setRheologyModel();
			void load(std::vector<CalcNode>& vertices, unsigned char indx);
			void checkTopology(real tau);
			RheologyModel* getRheologyModel();
	};
}
#endif	/* BLOCK_HPP */
