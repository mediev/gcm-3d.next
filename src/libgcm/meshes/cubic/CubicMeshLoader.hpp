#ifndef CUBICMESHLOADER_HPP
#define	CUBICMESHLOADER_HPP

#include "libgcm/meshes/cubic/CubicMesh.hpp"
#include "libgcm/Launcher.hpp"

namespace gcm {
	struct Geometry;
	
	class CubicMeshLoader {
	public:
		CubicMeshLoader();
		~CubicMeshLoader();
		void loadMesh(CubicMesh* mesh, Geometry geom, real h);
	private:

	};
}

#endif	/* CUBICMESHLOADER_HPP */

