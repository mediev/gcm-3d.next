#ifndef MESH2GEOLOADER_HPP_
#define MESH2GEOLOADER_HPP_

#include <string>
#include <fstream>
#include <utility>
#include <algorithm>
#include <map>
#include <cmath>

#include "libgcm/meshes/tetrahedron/TetrMeshFirstOrder.hpp"
#include "libgcm/util/Assertion.hpp"

typedef std::pair<int,int> Line;

namespace gcm {
	class CalcNode;
	class TetrMeshFirstOrder;

	class Mesh2GeoLoader
	{
	protected:
		std::vector<int> surfNums;
		std::map<Line,int> lineNums;
		std::map<Line,int>::iterator it;
		Line line1, line2;

		int getLineNum(int node1, int node2, int ordNum);

	public:
		Mesh2GeoLoader();
		~Mesh2GeoLoader();

		void writeGeoFile(std::string fileName, TetrMeshFirstOrder* mesh);
	};
}

#endif /* MESH2GEOLOADER_HPP_ */
