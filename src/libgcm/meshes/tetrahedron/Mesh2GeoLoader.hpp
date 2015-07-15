#ifndef MESH2GEOLOADER_HPP_
#define MESH2GEOLOADER_HPP_

#include "libgcm/meshes/tetrahedron/TetrMeshFirstOrder.hpp"
#include "libgcm/util/Singleton.hpp"

#include <fstream>

namespace gcm {
	class CalcNode;
	class TetrMeshFirstOrder;

	class Mesh2GeoLoader : public Singleton<Mesh2GeoLoader>{
	public:
		Mesh2GeoLoader();
		~Mesh2GeoLoader();

		std::string generateGeoFile(TetrMeshFirstOrder* mesh);
	};
}

#endif /* MESH2GEOLOADER_HPP_ */
