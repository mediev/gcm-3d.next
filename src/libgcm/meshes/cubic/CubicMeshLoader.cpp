#include "libgcm/meshes/cubic/CubicMeshLoader.hpp"

using namespace gcm;

void CubicMeshLoader::loadMesh(CubicMesh* mesh, Geometry geom, real h)
{
	int numX = (int) (geom.hx / h);
	int numY = (int) (geom.hy / h);
	int numZ = (int) (geom.hz / h);
	mesh->initValuesInNodes((numX + 1) * (numY + 1) * (numZ + 1));
    for( int k = 0; k <= numZ; k++ )
        for( int j = 0; j <= numY; j++ )
            for( int i = 0; i <= numX; i++ )
                mesh->createNode(geom.x0 + i*h, geom.y0 + j*h, geom.z0 + k*h);
	InertiaMomentPartitioner part;
	real *proportions = new real[3];
	part.partMesh(mesh, 4, proportions);
}
