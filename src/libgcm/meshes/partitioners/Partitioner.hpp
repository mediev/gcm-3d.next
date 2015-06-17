#ifndef PARTITIONER_HPP
#define	PARTITIONER_HPP

#include "libgcm/meshes/Mesh.hpp"

namespace gcm {
	class Partitioner {
	public:
		virtual void partMesh(Mesh *mesh, int N, real *proportions) = 0;

	};
}

#endif	/* PARTITIONER_HPP */

