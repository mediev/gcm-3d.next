#ifndef INERTIAMOMENTPARTITIONER_HPP
#define	INERTIAMOMENTPARTITIONER_HPP

#include "cstring"
#include "gsl/gsl_eigen.h"

#include "libgcm/meshes/partitioners/Partitioner.hpp"
#include "libgcm/util/Vector3.hpp"

namespace gcm {
	/**
	 * Class to divide mesh among processors using naive mass approach.
	 * Every node represents a unit mass. Partitioning is performed by
	 * finding the main axes of inertia tensor and dividing mesh 
	 * perpendicularly to them. 
	 */
	class InertiaMomentPartitioner : public Partitioner {
	public:
		void partMesh(Mesh *mesh, int N, real *proportions) override;
	private:
		void findInertiaTensorMinAxis(Mesh *mesh, const vector3r &rC, 
		                              vector3r &minAxis);
		void findBisectionParameters(Mesh *mesh, real p,
		                             vector3r &normal, vector3r &r0);
		void bisectMesh(Mesh *mesh, int N);

	};
}

#endif	/* INERTIAMOMENTPARTITIONER_HPP */

