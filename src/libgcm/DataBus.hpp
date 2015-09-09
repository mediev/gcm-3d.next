#ifndef DATABUS_HPP_
#define DATABUS_HPP_

#include "libgcm/util/Logging.hpp"
#include "libgcm/nodes/CalcNode.hpp"
#include "libgcm/meshes/tetrahedron/TetrMeshFirstOrder.hpp"
#include "libgcm/meshes/cubic/CubicMesh.hpp"

namespace gcm {
	class CalcNode;
	class TetraMeshFirstOrder;
	class CubicMesh;

	class DataBus {
	public:
		DataBus();
		~DataBus();

		// Transfer coarse mesh 0 -> all
		void transferMesh(TetrMeshFirstOrder* mesh);

		// Special types for MPI connection
		MPI::Datatype MPI_EMPTY_NODE;
		MPI::Datatype MPI_TETR;
		MPI::Datatype MPI_CUBE;

	private:

		// Rank of current core
		uint rank;
		// Number of cores
		uint numberOfWorkers;

		// Creates MPI::Datatype for node, tetrahedron, cube
		void createStaticTypes();


		// MPI tags for different types of messages
		static const int TAG_EMPTY_NODES = 1;
		static const int TAG_TETRS = 1000;
		static const int TAG_CUBES = 2000;

	};
}



#endif /* DATABUS_HPP_ */
