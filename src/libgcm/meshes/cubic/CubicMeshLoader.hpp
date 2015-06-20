#ifndef CUBICMESHLOADER_HPP
#define	CUBICMESHLOADER_HPP

#include "libgcm/meshes/cubic/CubicMesh.hpp"
#include "libgcm/meshes/partitioners/InertiaMomentPartitioner.hpp"
#include "libgcm/Launcher.hpp"

namespace gcm {
	struct Geometry;
	
	class CubicMeshLoader : public Singleton<CubicMeshLoader> {
	public:
		void loadMesh(CubicMesh* mesh, Geometry geom, real h);
	private:

	};
}

#endif	/* CUBICMESHLOADER_HPP */

