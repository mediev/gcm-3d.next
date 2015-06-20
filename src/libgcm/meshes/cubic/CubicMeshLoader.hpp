#ifndef CUBICMESHLOADER_HPP
#define	CUBICMESHLOADER_HPP

#include "libgcm/meshes/cubic/CubicMesh.hpp"
#include "libgcm/meshes/partitioners/InertiaMomentPartitioner.hpp"
#include "libgcm/Launcher.hpp"

namespace gcm {
	struct Geometry;
	
	class CubicMeshLoader : public Singleton<CubicMeshLoader> {
	public:
		CubicMeshLoader();
		void loadCoarseMesh(CubicMesh *mesh, Geometry geom, real h);
		void loadFineMeshFromCoarse(CubicMesh *coarse, CubicMesh *fine, real h);
	private:
		uint globalIndexOfNodes;

	};
}

#endif	/* CUBICMESHLOADER_HPP */

