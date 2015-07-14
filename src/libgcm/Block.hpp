#ifndef BLOCK_HPP
#define	BLOCK_HPP

#include "libgcm/Launcher.hpp"
#include "libgcm/Dispatcher.hpp"
#include "libgcm/meshes/cubic/CubicMeshLoader.hpp"
#include "libgcm/meshes/tetrahedron/TetrahedronMeshLoader.hpp"
#include "libgcm/solvers/GcmSolver.hpp"
#include "libgcm/rheologyModels/models/RheologyModel.hpp"
#include "libgcm/meshes/partitioners/MetisPartitioner.hpp"

namespace gcm {
	class Engine;
	struct BlockProperties;
	
	class Block
	{
	protected:
		uint id;
		GcmSolver* solver;
		RheologyModel* model;
		std::vector<Mesh*> meshes;
	public:
		Block();
		void loadTask(const BlockProperties &prop);
		void addMesh(Mesh *mesh);
		void doNextTimeStep();
		void checkTopology(real tau);
		void setId(uint _id);
		uint getId();
	};
}
#endif	/* BLOCK_HPP */
