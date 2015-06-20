#ifndef MSHTETRFILEREADER_HPP_
#define MSHTETRFILEREADER_HPP_

#include <string>
#include <fstream>
#include <limits>

#include "libgcm/meshes/tetrahedron/TetrMeshFirstOrder.hpp"
#include "libgcm/util/Assertion.hpp"

namespace gcm {
	class CalcNode;
	class TetrMeshFirstOrder;

	class MshTetrFileReader {
	public:
		MshTetrFileReader();
		~MshTetrFileReader();

		void readFile(std::string file, TetrMeshFirstOrder* mesh);
	};
}

#endif /* SRC_LIBGCM_MESHES_TETRAHEDRON_MSHTETRFILEREADER_HPP_ */
