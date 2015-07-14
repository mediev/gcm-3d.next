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
		/**
		 * Divide mesh into N meshes with respect to proportions.
         * @param block pointer to Block that owns the mesh
         * @param mesh mesh to divide
         * @param proportions map<processor's rank, processor's load>
		 * with proportions to divide the mesh among workers
         */
		void partMesh(Block *block, Mesh *mesh, const std::map<uint, real>& propsMap);
	private:
		void findInertiaTensorMinAxis(Mesh *mesh, const vector3r &rC, 
		                              vector3r &minAxis);
		void findBisectionParameters(Mesh *mesh, real p,
		                             vector3r &normal, vector3r &r0);
		void bisectMesh(Block *block, Mesh *mesh, uint N, real* proportions, uint *ranks);
		/**
		 * Balance the array around its center N/2.
		 * Then recursively balance two resulting arrays...
         * @param arr array to balance
         * @param N size of array
         */
		void fractalBalance(real *arr, uint *ranks, uint N);

	};
}

#endif	/* INERTIAMOMENTPARTITIONER_HPP */

