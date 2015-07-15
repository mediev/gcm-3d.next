#ifndef METISPARTITIONER_HPP_
#define METISPARTITIONER_HPP_

#include "libgcm/Block.hpp"
#include "libgcm/util/Singleton.hpp"
#include "libgcm/meshes/tetrahedron/TetrMeshFirstOrder.hpp"
#include "libgcm/meshes/cubic/CubicMesh.hpp"

#include <memory>
#include <algorithm>
#include "metis.h"

namespace gcm
{
	class Block;
	class TetrMeshFirstOrder;
	class CubicMesh;

	class MetisPartitioner : public Singleton<MetisPartitioner>
	{

	public:
		MetisPartitioner();
		~MetisPartitioner();

		void partMesh(TetrMeshFirstOrder* mesh, const uint nparts, TetrMeshFirstOrder* coarsePart);
		void partMesh(CubicMesh* mesh, const uint nparts, CubicMesh* coarsePart);
	};

}

#endif /* METISPARTITIONER_HPP_ */
