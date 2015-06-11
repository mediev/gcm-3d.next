#ifndef CUBICMESH_HPP
#define	CUBICMESH_HPP

#include "libgcm/meshes/Mesh.hpp"

namespace gcm {
	class CubicMesh : public Mesh {
	public:
		CubicMesh();
		CubicMesh(const CubicMesh& orig);
		~CubicMesh();
		void checkTopology(float tau) override;

	private:

	};
}

#endif	/* CUBICMESH_HPP */

