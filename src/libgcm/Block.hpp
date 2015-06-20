#ifndef BLOCK_HPP
#define	BLOCK_HPP

#include "libgcm/Launcher.hpp"
#include "libgcm/meshes/cubic/CubicMeshLoader.hpp"
#include "libgcm/meshes/tetrahedron/TetrahedronMeshLoader.hpp"
#include "libgcm/solvers/GcmSolver.hpp"
#include "libgcm/rheologyModels/models/RheologyModel.hpp"

namespace gcm {
	class Engine;
	struct BlockProperties;
	
	class Block
	{
	protected:
		std::string name;
		GcmSolver* solver;
		RheologyModel* model;
		std::vector<Mesh*> meshes;
	public:
		Block(const BlockProperties &prop);
		void doNextTimeStep();
		void checkTopology(real tau);
	};
}
#endif	/* BLOCK_HPP */
