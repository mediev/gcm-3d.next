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
    for( uint k = 0; k <= numZ; k++ )
        for( uint j = 0; j <= numY; j++ )
            for( uint i = 0; i <= numX; i++ ) {
                CalcNode node = newNode(rModel->getNodeType());
                node.number = globalIndexOfNodes; globalIndexOfNodes++;
                node.coords[0] = geom.x0 + i*h;
                node.coords[1] = geom.y0 + j*h;
                node.coords[2] = geom.z0 + k*h;
                mesh->addNode(node);
			}

	mesh->initElements(numX * numY * numZ);
	for( uint k = 0; k < numZ; k++ )
        for( uint j = 0; j < numY; j++ )
            for( uint i = 0; i < numX; i++ ) {
				uint vertices[8];
				vertices[0] =  k      * (numX+1) * (numY+1) +  j      * (numX+1) +  i;
				vertices[1] =  k      * (numX+1) * (numY+1) +  j      * (numX+1) + (i + 1);
				vertices[2] =  k      * (numX+1) * (numY+1) + (j + 1) * (numX+1) +  i;
				vertices[3] =  k      * (numX+1) * (numY+1) + (j + 1) * (numX+1) + (i + 1);
				vertices[4] = (k + 1) * (numX+1) * (numY+1) +  j      * (numX+1) +  i;
				vertices[5] = (k + 1) * (numX+1) * (numY+1) +  j      * (numX+1) + (i + 1);
				vertices[6] = (k + 1) * (numX+1) * (numY+1) + (j + 1) * (numX+1) +  i;
				vertices[7] = (k + 1) * (numX+1) * (numY+1) + (j + 1) * (numX+1) + (i + 1);
				Cube cube = Cube(vertices[0], vertices);
				mesh->addElement(cube);
			}
    mesh->preProcess();
}

void CubicMeshLoader::loadFineMeshFromCoarse(CubicMesh* coarse, CubicMesh *fine, real h) {
	uint elementsNum = coarse->getElementsNumber();
	assert(elementsNum > 0);
	Cube &tmpCube = static_cast<Cube &>(coarse->getElementByLocalIndex(0));
	CalcNode node1 = coarse->getNode(tmpCube.vertices[0]);
	CalcNode node2 = coarse->getNode(tmpCube.vertices[1]);
	// how many fine cubes go along edge of coarse cube
	uint refinement = (uint) ( fabs(node1.coords[0] - node2.coords[0]) / h );
	// assert if step of coarse mesh is divisible by step of fine mesh
	assert(( refinement - ( fabs(node1.coords[0] - node2.coords[0]) / h ) ) == 0);
	
	for (uint i = 0; i < elementsNum; i++) {
		Cube &coarseCube = static_cast<Cube &>(coarse->getElementByLocalIndex(i));
		CalcNode coarseNode = coarse->getNode(coarseCube.vertices[0]);
		for(uint k = 0; k < refinement; k++)
			for(uint j = 0; j < refinement; j++)
				for(uint i = 0; i < refinement; i++) {
					// coords of 1'st vertice of fineCube
					vector3r r = coarseNode.coords;
					r.coords[0] += i*h; r.coords[1] += j*h; r.coords[2] += k*h;
					CalcNode fineNode = node1;
					fineNode.coords = r + vector3r(0, 0 , 0);
					
					fineNode.coords = r + vector3r(h, 0 , 0);
					
					fineNode.coords = r + vector3r(0, h , 0);
					
					fineNode.coords = r + vector3r(h, h , 0);
					
					fineNode.coords = r + vector3r(0, 0 , h);
					
					fineNode.coords = r + vector3r(h, 0 , h);
					
					fineNode.coords = r + vector3r(0, h , h);
					
					fineNode.coords = r + vector3r(h, h , h);
					
					
					Cube fineCube;
					
					//mesh->addElementWithNodes(cube, mesh);
				}
	}
	coarse->~Mesh();
	fine->initValuesInNodes();
}
