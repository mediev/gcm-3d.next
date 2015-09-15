#include "libgcm/meshes/cubic/CubicMeshLoader.hpp"
#include "libgcm/snapshotters/VTKCubicSnapshotWriter.hpp"

using namespace gcm;

CubicMeshLoader::CubicMeshLoader() {
	globalIndexOfNodes = 0;
}

void CubicMeshLoader::loadCoarseMesh(CubicMesh* mesh, Geometry geom, real h)
{
	uint numX = (uint) (geom.hx / h);
	uint numY = (uint) (geom.hy / h);
	uint numZ = (uint) (geom.hz / h);
	RheologyModel* rModel = mesh->getRheologyModel();
	
	mesh->initNodesWithoutValues((numX+1)*(numY+1)*(numZ+1));
	uint startGlobalIndex = globalIndexOfNodes;
    for( uint k = 0; k <= numZ; k++ )
        for( uint j = 0; j <= numY; j++ )
            for( uint i = 0; i <= numX; i++ ) {
                CalcNode node = getNewNode(rModel->getNodeType());
                node.number = globalIndexOfNodes; globalIndexOfNodes++;
                node.coords[0] = geom.x0 + i*h;
                node.coords[1] = geom.y0 + j*h;
                node.coords[2] = geom.z0 + k*h;
                mesh->addNodeWithoutValues(node);
			}

	mesh->initElements(numX * numY * numZ);
	for( uint k = 0; k < numZ; k++ )
        for( uint j = 0; j < numY; j++ )
            for( uint i = 0; i < numX; i++ ) {
				uint vertices[8];
				vertices[0] =  k      * (numX+1) * (numY+1) +  j      * (numX+1) +  i      + startGlobalIndex;
				vertices[1] =  k      * (numX+1) * (numY+1) +  j      * (numX+1) + (i + 1) + startGlobalIndex;
				vertices[2] =  k      * (numX+1) * (numY+1) + (j + 1) * (numX+1) +  i      + startGlobalIndex;
				vertices[3] =  k      * (numX+1) * (numY+1) + (j + 1) * (numX+1) + (i + 1) + startGlobalIndex;
				vertices[4] = (k + 1) * (numX+1) * (numY+1) +  j      * (numX+1) +  i      + startGlobalIndex;
				vertices[5] = (k + 1) * (numX+1) * (numY+1) +  j      * (numX+1) + (i + 1) + startGlobalIndex;
				vertices[6] = (k + 1) * (numX+1) * (numY+1) + (j + 1) * (numX+1) +  i      + startGlobalIndex;
				vertices[7] = (k + 1) * (numX+1) * (numY+1) + (j + 1) * (numX+1) + (i + 1) + startGlobalIndex;
				Cube cube = Cube(vertices[0], vertices);
				mesh->addElement(cube);
			}
    mesh->preProcess();
}

void CubicMeshLoader::loadFineMeshFromCoarse(CubicMesh* coarse, CubicMesh *fine, 
                                             real h) {
	fine->setRank(coarse->getRank());
	fine->setId(coarse->getId());
	CalcNode node1 = coarse->getNodeByLocalIndex(0);
	
	AABB outline = coarse->getOutline();
	uint Nz = (uint) ((outline.maxZ - outline.minZ) / h) + 1;
	uint Ny = (uint) ((outline.maxY - outline.minY) / h) + 1;
	uint Nx = (uint) ((outline.maxX - outline.minX) / h) + 1;
	fine->initNodesWithoutValues( (Nx+1) * (Ny+1) * (Nz+1) );
	// TODO - fix adequate global indexation
	globalIndexOfNodes = MPI::COMM_WORLD.Get_rank() * 10000000;
	for (uint k = 0; k <= Nz; k++)
		for (uint j = 0; j <= Ny; j++)
			for (uint i = 0; i <= Nx; i++) {
				real x = outline.minX + i*h;
				real y = outline.minY + j*h;
				real z = outline.minZ + k*h;
				if ( coarse->hasPoint(vector3r(x, y, z)) ) {
					node1.coords = vector3r(x, y, z);
					node1.number = globalIndexOfNodes; globalIndexOfNodes++;
					fine->addNodeWithoutValues(node1);
				}
			}
	
	coarse->~Mesh();
	fine->initValuesInNodes();
	fine->preProcess();
}
