#ifndef TETRAHEDRONMESHLOADER_HPP
#define	TETRAHEDRONMESHLOADER_HPP

#include <string>
#include <map>

#include "libgcm/meshes/tetrahedron/TetrMeshFirstOrder.hpp"
#include "libgcm/meshes/tetrahedron/MshTetrFileReader.hpp"
#include "libgcm/Launcher.hpp"

#include <gmsh/Gmsh.h>
#include <gmsh/GModel.h>
#include <gmsh/GEntity.h>
#include <gmsh/MElement.h>
#include <gmsh/MVertex.h>
#include <gmsh/MTriangle.h>
#include <gmsh/MTetrahedron.h>

namespace gcm {
	class CalcNode;
	class TetrMeshFirstOrder;

	class TetrahedronMeshLoader : public Singleton<TetrahedronMeshLoader>
	{
	protected:
		USE_LOGGER;

		// Return expected *.msh file name
		std::string getMshFileName(std::string geoFile);
		// Return expected *.vtu file name
		std::string getVtkFileName(std::string geoFile);
		// Write *.msh file from *.geo file
		void createMshFile(std::string fileName, real tetrSize);
		// Answer: does any *.msh file exist with this file name
		bool isMshFileCreated(std::string fileName);

		std::map<std::string,bool> createdFiles;
	public:
		TetrahedronMeshLoader();
		~TetrahedronMeshLoader();

		void loadMesh(TetrMeshFirstOrder* mesh, std::string fileName, real tetrSize);
        void cleanUp();
	private:

	};
}

#endif	/* TETRAHEDRONMESHLOADER_HPP */

