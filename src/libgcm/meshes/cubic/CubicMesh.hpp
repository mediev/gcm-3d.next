#ifndef CUBICMESH_HPP
#define	CUBICMESH_HPP

#include "libgcm/meshes/Mesh.hpp"

namespace gcm {
	class CubicMesh : public Mesh {
	public:
		CubicMesh();
		~CubicMesh();
		void checkTopology(float tau) override;
		Mesh* getMeshOfTheSameType() override;


	private:

	};
}

#endif	/* CUBICMESH_HPP */

