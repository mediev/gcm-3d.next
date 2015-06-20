#include "libgcm/meshes/cubic/CubicMesh.hpp"
#include "libgcm/snapshotters/VTKCubicSnapshotWriter.hpp"

using namespace gcm;
using std::numeric_limits;

CubicMesh::CubicMesh() {
	meshH = numeric_limits<real>::infinity();
	type = "CubicMesh";
	movable = false;
}

CubicMesh::~CubicMesh() {
	nodes.clear();
}

Mesh* CubicMesh::getMeshOfTheSameType() {
	return new CubicMesh();
}

void CubicMesh::preProcessGeometry()
{
	// TODO: Finish the function
    /*for(int i = 0; i < getNodesNumber(); i++)
    {
        CalcNode& node = getNodeByLocalIndex(i);
        for( int i = 0; i < 3; i ++)
        {
            if( ( fabs(node.coords[i] - outline.min_coords[i]) < EQUALITY_TOLERANCE )
                || ( fabs(node.coords[i] - outline.max_coords[i]) < EQUALITY_TOLERANCE ) )
            {
                node.setBorder(true);
            }
        }
    }*/
}

void CubicMesh::calcMinH()
{
	meshH = fabs(getNodeByLocalIndex(0).coords[0] - getNodeByLocalIndex(1).coords[0]);
};

real CubicMesh::getMinH()
{
    if( isinf( meshH ) )
        calcMinH();
    return meshH;
};

void CubicMesh::createOutline()
{
}

void CubicMesh::checkTopology(float tau) {
}

const SnapshotWriter& CubicMesh::getSnaphotter() const
{
    return VTKCubicSnapshotWriter::getInstance();
}
