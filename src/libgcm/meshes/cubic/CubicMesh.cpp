#include "libgcm/meshes/cubic/CubicMesh.hpp"

using namespace gcm;
using std::numeric_limits;

CubicMesh::CubicMesh() {
	meshH = numeric_limits<real>::infinity();
	type = "CubicMesh";
	movable = false;
}

CubicMesh::CubicMesh(const CubicMesh& orig) {
}

CubicMesh::~CubicMesh() {
	nodes.clear();
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
    if( getNodesNumber() < 2)
        return;

    CalcNode& base = getNodeByLocalIndex(0);
    real h;

    // We suppose that mesh is uniform
    for(int i = 1; i < getNodesNumber(); i++)
    {
        CalcNode& node = getNodeByLocalIndex(i);
        h = distance(base.coords, node.coords);
        if( h < meshH )
            meshH = h;
    }

    // TODO - we should auto-scale mesh transparently in this case
    if( meshH < EQUALITY_TOLERANCE )
    {
        //LOG_WARN("Mesh minH is too small: minH " << meshH << ", FP tolerance: " << EQUALITY_TOLERANCE);
        //LOG_WARN("Fixing it automatically, but it can cause numerous intersting issues");
        meshH = 10 * EQUALITY_TOLERANCE;
    }
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

void CubicMesh::checkTopology(float tau)
{
}
