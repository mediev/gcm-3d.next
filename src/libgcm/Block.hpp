#ifndef BLOCK_HPP
#define	BLOCK_HPP

#include "libgcm/Launcher.hpp"
#include "libgcm/Dispatcher.hpp"
#include "libgcm/meshes/cubic/CubicMeshLoader.hpp"
#include "libgcm/meshes/tetr/TetrMeshLoader.hpp"
#include "libgcm/solvers/Solver.hpp"
#include "libgcm/rheologyModels/models/RheologyModel.hpp"
#include "libgcm/meshes/partitioners/MetisPartitioner.hpp"

namespace gcm {
	class Engine;
	struct BlockProperties;
	
	class Block
	{
	protected:
		uint id;
		Solver* solver;
		RheologyModel* model;
		std::vector<Mesh*> meshes;

	public:
		Block();
		void loadTask(const BlockProperties &prop);
		void addMesh(Mesh *mesh);
		void doNextTimeStep();
		void replaceNewAndCurrentNodes();
		void checkTopology(real tau);
		void setId(uint _id);
		uint getId();
	};
}
#endif	/* BLOCK_HPP */
