#ifndef MESH2MSHLOADER_HPP_
#define MESH2MSHLOADER_HPP_

#include "libgcm/meshes/tetrahedron/TetrMeshFirstOrder.hpp"
#include "libgcm/util/Assertion.hpp"
#include "libgcm/util/Singleton.hpp"

#include <fstream>

namespace gcm {
	class CalcNode;
	class TetrMeshFirstOrder;

	class Mesh2MshLoader : public Singleton<Mesh2MshLoader> {
	public:
		Mesh2MshLoader();
		~Mesh2MshLoader();

		std::string generateMshFile(TetrMeshFirstOrder* mesh);
	};

}

#endif /* MESH2MSHLOADER_HPP_ */
