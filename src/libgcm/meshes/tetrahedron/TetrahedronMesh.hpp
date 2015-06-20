#ifndef TETRAHEDRONMESH_HPP
#define	TETRAHEDRONMESH_HPP

#include "libgcm/meshes/Mesh.hpp"
#include "libgcm/elements/TetrahedronFirstOrder.hpp"
#include "libgcm/elements/TriangleFirstOrder.hpp"

namespace gcm {
	class TetrahedronMesh : public Mesh {
	public:
		TetrahedronMesh();
		virtual ~TetrahedronMesh();
        
        virtual int getTetrsNumber() = 0;
        virtual int getTriangleNumber() = 0;

        virtual void addTetr(TetrahedronFirstOrder& tetr) = 0;

        virtual TetrahedronFirstOrder& getTetr(uint index) = 0;

        virtual TetrahedronFirstOrder& getTetrByLocalIndex(uint index) = 0;

        virtual TriangleFirstOrder& getTriangle(uint index) = 0;

        virtual bool hasTetr(unsigned int index) = 0;

        virtual void createTetrs(int number) = 0;

        virtual void createTriangles(int number) = 0;
		
		virtual bool belongsToTetrahedron(uint nodeNum, int tetrNum, int faceNum) = 0;
	
	private:

	};
}

#endif	/* TETRAHEDRONMESH_HPP */

