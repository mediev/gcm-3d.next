#ifndef INERTIAMOMENTPARTITIONER_HPP
#define	INERTIAMOMENTPARTITIONER_HPP

#include "cstring"
#include "gsl/gsl_eigen.h"

#include "libgcm/util/Vector3.hpp"
#include "libgcm/meshes/Mesh.hpp"
#include "libgcm/Block.hpp"

namespace gcm {
	class Block;
	class Mesh;
	/**
	 * Class to divide mesh into N new meshes using naive mass approach.
	 * Every element represents a unit mass at its center.
	 * Partitioning is performed by recursive finding the main axes
	 * of inertia tensor and dividing mesh perpendicularly to the minimal axis 
	 */
	class InertiaMomentPartitioner {
	public:
		void partMesh(Block *block, Mesh *mesh, int N, real *proportions);
	private:
		void findInertiaTensorMinAxis(Mesh *mesh, const vector3r &rC, 
		                              vector3r &minAxis);
		void findBisectionParameters(Mesh *mesh, real p,
		                             vector3r &normal, vector3r &r0);
		void bisectMesh(Block *block, Mesh *mesh, int N, real* proportions);

	};
}

#endif	/* INERTIAMOMENTPARTITIONER_HPP */

