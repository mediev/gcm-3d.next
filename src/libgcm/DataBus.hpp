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

		void transferMesh(TetrMeshFirstOrder* mesh, uint targetRank);

		// Special types for MPI connection
		MPI::Datatype MPI_EMPTY_NODE;
		MPI::Datatype MPI_TETR;
		MPI::Datatype MPI_CUBE;

	private:

		// Rank of current core
		uint rank;

		// Creates MPI::Datatype for node, tetrahedron, cube
		void createStaticTypes();
	};
}



#endif /* DATABUS_HPP_ */
