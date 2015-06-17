#include "libgcm/meshes/cubic/CubicMeshLoader.hpp"

using namespace gcm;

void CubicMeshLoader::loadMesh(CubicMesh* mesh, Geometry geom, real h)
{
	int numX = (int) (geom.hx / h);
	int numY = (int) (geom.hy / h);
	int numZ = (int) (geom.hz / h);
	mesh->initValuesInNodes((numX + 1) * (numY + 1) * (numZ + 1));
	RheologyModel* rModel = mesh->getRheologyModel();
	
	int n = 0;
    for( int k = 0; k <= numZ; k++ )
        for( int j = 0; j <= numY; j++ )
            for( int i = 0; i <= numX; i++ ) {
                CalcNode node = newNode(rModel->getNodeType());
                node.number = n;
                node.coords[0] = geom.x0 + i*h;
                node.coords[1] = geom.y0 + j*h;
                node.coords[2] = geom.z0 + k*h;
                mesh->addNode(node);
                n++;
			}
	
	InertiaMomentPartitioner part;
	real *proportions = new real[3];
	part.partMesh(mesh, 4, proportions);
}
