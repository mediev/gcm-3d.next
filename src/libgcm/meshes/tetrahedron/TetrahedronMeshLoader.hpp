#ifndef TETRAHEDRONMESHLOADER_HPP
#define	TETRAHEDRONMESHLOADER_HPP

#include "libgcm/meshes/tetrahedron/TetrahedronMesh.hpp"
#include "libgcm/Launcher.hpp"

namespace gcm {
	
	class TetrahedronMeshLoader : public Singleton<TetrahedronMeshLoader>{
	public:
		TetrahedronMeshLoader();
		~TetrahedronMeshLoader();

		void loadMesh(TetrahedronMesh* mesh, std::string meshFile, real h);
	private:

	};
}

#endif	/* TETRAHEDRONMESHLOADER_HPP */

