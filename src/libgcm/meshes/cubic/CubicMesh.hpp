#ifndef CUBICMESH_HPP
#define	CUBICMESH_HPP

#include "libgcm/meshes/Mesh.hpp"
#include "libgcm/util/Math.hpp"

namespace gcm {
	class CubicMesh : public Mesh {

	protected:
		void calcMinH();
		void preProcessGeometry();

		real meshH;
	public:
		CubicMesh();
		~CubicMesh();

		Mesh* getMeshOfTheSameType() override;
		
		// Redefining of virtual methods
		void checkTopology(real tau) override;
		void createOutline();
		real getMinH();

		virtual const SnapshotWriter& getSnaphotter() const override;

	private:

	};
}

#endif	/* CUBICMESH_HPP */

