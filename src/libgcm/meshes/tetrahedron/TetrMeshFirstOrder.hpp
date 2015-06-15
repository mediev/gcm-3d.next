#ifndef TETR_MESH_FIRST_ORDER_HPP
#define TETR_MESH_FIRST_ORDER_HPP

#include <unordered_map>
#include <algorithm>

#include "libgcm/elements/TetrahedronFirstOrder.hpp"
#include "libgcm/elements/TriangleFirstOrder.hpp"

#include "libgcm/meshes/tetrahedron/TetrahedronMesh.hpp"
#include "libgcm/elements/TetrahedronFirstOrder.hpp"
#include "libgcm/elements/TriangleFirstOrder.hpp"

namespace gcm {
	
	class TetrMeshFirstOrder : public TetrahedronMesh {
	protected:

	public:
		TetrMeshFirstOrder();
		virtual ~TetrMeshFirstOrder();

        int getTetrsNumber();
        int getTriangleNumber();

		void addTetr(TetrahedronFirstOrder& tetr);

		TetrahedronFirstOrder& getTetr(unsigned int index);
		TetrahedronFirstOrder& getTetrByLocalIndex(unsigned int index);

		TriangleFirstOrder& getTriangle(int index);

		bool hasTetr(unsigned int index);

		void createTetrs(int number);

		void createTriangles(int number);

		bool belongsToTetrahedron(int nodeNum, int tetrNum, int faceNum);

		void checkTopology(float tau) override;
	};
	
}

#endif /* TETR_MESH_FIRST_ORDER_HPP */
