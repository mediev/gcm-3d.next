#include "libgcm/meshes/tetrahedron/TetrMeshFirstOrder.hpp"

using namespace gcm;
using std::vector;
using std::unordered_map;
using std::numeric_limits;
using std::make_pair;

TetrMeshFirstOrder::TetrMeshFirstOrder()
{
	tetrStorageSize = 0;
	tetrsNumber = 0;
	faceStorageSize = 0;
	facesNumber = 0;

	mesh_min_h = numeric_limits<real>::infinity();
	mesh_max_h = numeric_limits<real>::infinity();
	mesh_avg_h = numeric_limits<real>::infinity();
	mesh_max_edge = numeric_limits<real>::infinity();

	cacheHits = 0;
	cacheMisses = 0;
}

TetrMeshFirstOrder::~TetrMeshFirstOrder()
{
	nodes.clear();
	tetrs1.clear();
	borders1.clear();
}

void TetrMeshFirstOrder::preProcessGeometry()
{
    calcMaxH();
    calcAvgH();
    calcMaxEdge();

    //verifyTetrahedraVertices ();
    build_volume_reverse_lookups();

    //check_unused_nodes();
    build_border();
    build_surface_reverse_lookups();
}

void TetrMeshFirstOrder::build_volume_reverse_lookups()
{
	int i;

	// Clearing
	for( MapIter itr = nodesMap.begin(); itr != nodesMap.end(); ++itr ) {
		i = itr->first;
		getVolumeElementsForNode(i).clear();
	}

	// Filling
	for( MapIter itr = tetrsMap.begin(); itr != tetrsMap.end(); ++itr ) {
		i = itr->first;
		TetrahedronFirstOrder& tetr = getTetr(i);

		for(int j = 0; j < 4; j++) {
			//CalcNode& node = getNode(tetr.vertices[j]);
			//assert(node.isFirstOrder());
			getVolumeElementsForNode(tetr.vertices[j]).push_back(tetr.number);
		}
	}
}

void TetrMeshFirstOrder::build_border()
{
    // Prepare border data
    float solid_angle;
    float solid_angle_part;

    int nodeCount = 0;
    int i;

    // Check border using solid angle comparation with 4*PI
    for( MapIter itr = nodesMap.begin(); itr != nodesMap.end(); ++itr ) {
        i = itr->first;
        CalcNode& node = getNode(i);
        node.setBorder(false);
        // We consider remote nodes to be 'border' of current local ones
        if( true/*node.isLocal() && node.isFirstOrder()*/ )
        {
            solid_angle = 0.0;
            vector<int>& elements = getVolumeElementsForNode(i);
            for(unsigned j = 0; j < elements.size(); j++)
            {
                solid_angle_part = get_solid_angle(i, elements[j]);
                assert_ge(solid_angle_part, 0);
                solid_angle += solid_angle_part;
            }
            if( fabs(4 * M_PI - solid_angle) > M_PI * EQUALITY_TOLERANCE ) {
                node.setBorder (true);
                nodeCount++;
            }
        }
    }
    printf("Found %d border nodes\n", nodeCount);

    //Constructing border triangles;
    int faceCount = 0;
    int number = 0;

    // FIXME TODO - make faces uniq!

    // Check all tetrs and construct border triangles
    //for(int i = 0; i < tetrsNumber; i++) {
    for( MapIter itr = tetrsMap.begin(); itr != tetrsMap.end(); ++itr ) {
        i = itr->first;
        TetrahedronFirstOrder& tetr = getTetr(i);
        for( int j = 0; j < 4; j++ )
        {
            if( isTriangleBorder( tetr.vertices ) )
                faceCount++;
            shiftArrayLeft( tetr.vertices, 4 );
        }
    }

    printf("Found %d border triangles\n", faceCount);

    createTriangles(faceCount);

    for( MapIter itr = tetrsMap.begin(); itr != tetrsMap.end(); ++itr ) {
        i = itr->first;
        TetrahedronFirstOrder& tetr = getTetr(i);
        for( int j = 0; j < 4; j++ )
        {
            if( isTriangleBorder( tetr.vertices ) )
            {
                addTriangle(*createBorderTriangle( tetr.vertices, number ) );
                number++;
            }
            shiftArrayLeft( tetr.vertices, 4 );
        }
    }

    assert_eq(number, faceCount);
    printf("Created %d triangles\n", facesNumber);
}

real TetrMeshFirstOrder::get_solid_angle(int node_index, int tetr_index)
{
	TetrahedronFirstOrder& tetr = getTetr(tetr_index);
	CalcNode& node = getNode(node_index);

	int verts[3];
	int count = 0;
    for(int i = 0; i < 4; i++)
        if(tetr.vertices[i] != node_index) {
            verts[count] = tetr.vertices[i];
            count++;
        }

    // Node should belong to tetr
    assert(count == 3);

    CalcNode& v0 = getNode( verts[0] );
    CalcNode& v1 = getNode( verts[1] );
    CalcNode& v2 = getNode( verts[2] );

    return solidAngle(v0.coords - node.coords, v1.coords - node.coords, v2.coords - node.coords);
}

TriangleFirstOrder* TetrMeshFirstOrder::createBorderTriangle(uint v[4], uint number)
{
    bool needSwap;
    bool isBorder;
    isBorder = isTriangleBorder( v, &needSwap );
    assert_true(isBorder );

    // Create and return triangle
    TriangleFirstOrder* tri = new TriangleFirstOrder();
    if( !needSwap ) {
        tri->vertices[0] = v[0];
        tri->vertices[1] = v[1];
        tri->vertices[2] = v[2];
    } else {
        tri->vertices[0] = v[0];
        tri->vertices[1] = v[2];
        tri->vertices[2] = v[1];
    }
    return tri;
}

bool TetrMeshFirstOrder::isTriangleBorder(uint v[4])
{
    bool needSwap;
    return isTriangleBorder( v, &needSwap, false );
}

bool TetrMeshFirstOrder::isTriangleBorder(uint v[4], bool debug)
{
    bool needSwap;
    return isTriangleBorder( v, &needSwap, debug );
}

bool TetrMeshFirstOrder::isTriangleBorder(uint v[4], bool* needSwap)
{
    return isTriangleBorder( v, needSwap, false );
}

bool TetrMeshFirstOrder::isTriangleBorder(uint v[4], bool* needSwap, bool debug)
{
    *needSwap = false;
    CalcNode& v1 = getNode( v[0] );
    CalcNode& v2 = getNode( v[1] );
    CalcNode& v3 = getNode( v[2] );
    CalcNode& tetr_vert = getNode( v[3] );

    if( !v1.isBorder() || !v2.isBorder() || !v3.isBorder() )
        return false;

    //bool _debug = debug;

    real h = getMinH() * 0.25;

    // Normal vector
    vector3r normal;
    // Displacement
    vector3r dx;

    vector3r center;
    vector3r innerDirection;
    vector3r plane_move;
    // gcm::real plane_move_mod;

    findTriangleFaceNormal(v1.coords, v2.coords, v3.coords, normal);

    // Triangle center
    center = (v1.coords + v2.coords + v3.coords) / 3;

    // Direction from triangle center to the verticle of tetrahedron
    innerDirection = tetr_vert.coords - center;

    // Check if normal is co-linear with tetr verticle direction
    if( normal * innerDirection > 0.0 )
    {
        // If they are - invert normal because only opposite direction can be outer
        normal = -normal;
        // And swap verticles order to match new direction
        //v2 = getNode( v[2] );
        //v3 = getNode( v[1] );
        *needSwap = true;
    }

    // Displacement along potential outer normal
    dx = h * normal;

    // Move from v1 to triangle center
    plane_move = center - v1.coords;

    dx += plane_move;

    // Check if we are outside of the body moving from triangle center along normal ...
    if( fastScanForOwnerTetr(v1, dx) != -1 )
        return false;

    return true;
};

int TetrMeshFirstOrder::fastScanForOwnerTetr(const CalcNode& node, const vector3r& dx)
{
    int res;
    if( charactCacheAvailable() )
    {
        if( checkCharactCache(node, dx, res) )
        {
            cacheHits++;
            return res;
        }
        cacheMisses++;
    }

    vector3r x = node.coords + dx;

    // Disable it since it causes issues with parallel computation
    // - it becomes not clear how we should use here outline, expandedOutline, 'zone of interest'
    /*if( ! outline.isInAABB(x, y, z) )
    {
        if( debug )
            LOG_TRACE("Not in AABB");
        return -1;
    }*/

    vector<int>& elements = getVolumeElementsForNode(node.number);

    for(unsigned i = 0; i < elements.size(); i++)
    {
        TetrahedronFirstOrder& tetr = getTetr(elements[i]);
        if( pointInTetr(x,
                getNode( tetr.vertices[0] ).coords, getNode( tetr.vertices[1] ).coords,
                getNode( tetr.vertices[2] ).coords, getNode( tetr.vertices[3] ).coords) )
        {
            updateCharactCache(node, dx, tetr.number);
            return tetr.number;
        }
    }

    updateCharactCache(node, dx, -1);
    return -1;
}

bool TetrMeshFirstOrder::charactCacheAvailable()
{
	return false;
}

bool TetrMeshFirstOrder::checkCharactCache(const CalcNode& node, const vector3r& dx, int& tetrNum)
{
    int cacheIndex = getCharactCacheIndex(node, dx);
    MapIter itr;
    itr = charactCache[cacheIndex].find(node.number);
    if( itr == charactCache[cacheIndex].end() )
        return false;
    tetrNum = itr->second;
    if( tetrNum == -1 )
        return false;
    TetrahedronFirstOrder& curTetr = getTetr(tetrNum);
    return pointInTetr(
                    node.coords + dx,
                    getNode( curTetr.vertices[0] ).coords,
                    getNode( curTetr.vertices[1] ).coords,
                    getNode( curTetr.vertices[2] ).coords,
                    getNode( curTetr.vertices[3] ).coords);
}

void TetrMeshFirstOrder::updateCharactCache(const CalcNode& node, const vector3r& x, int tetrNum)
{
    if( !charactCacheAvailable() )
        return;
    int cacheIndex = getCharactCacheIndex(node, x);
    charactCache[cacheIndex][node.number] = tetrNum;
}

int TetrMeshFirstOrder::getCharactCacheIndex(const CalcNode& node, const vector3r& dx)
{
    real fdx = fabs(dx[0]);
    real fdy = fabs(dx[1]);
    real fdz = fabs(dx[2]);

    // FIXME ASAP: calling m.createAi() on each cache index access is horrible for performance
    RheologyMatrixPtr m = node.getRheologyMatrix();

    short sign = -1;
    short direction = -1;
    if( fdx > fdy )
        if( fdx > fdz )
        {
            direction = 1;
            m->decomposeX(node);
            sign = (dx[0] > 0 ? 2 : 1);
        }
        else
        {
            direction = 3;
            m->decomposeZ(node);
            sign = (dx[2] > 0 ? 2 : 1);
        }
    else
        if( fdy > fdz )
        {
            direction = 2;
            m->decomposeY(node);
            sign = (dx[1] > 0 ? 2 : 1);
        }
        else
        {
            direction = 3;
            m->decomposeZ(node);
            sign = (dx[2] > 0 ? 2 : 1);
        }

    real l2 = dx * dx;
    real tau = Engine::getInstance().getTimeStep();


    float maxV = m->getMaxEigenvalue();
    float minV = m->getMinEigenvalue();

    short scale = -1;
    if( fabs(l2 - tau*tau*maxV*maxV) < l2 * EQUALITY_TOLERANCE )
        scale = 3;
    else if( fabs(l2 - tau*tau*minV*minV) < l2 * EQUALITY_TOLERANCE )
        scale = 1;
    else
        scale = 2;

    assert_gt(direction, 0);
    assert_lt(direction, 4);
    assert_gt(scale, 0);
    assert_lt(scale, 4);
    assert_true(sign == 1 || sign == 2);

    return (direction - 1)*6 + (sign-1)*3 + (scale-1);
}

/*void TetrMeshFirstOrder::find_border_elem_normal(int border_element_index, real* x, real* y, real* z)
{
    TriangleFirstOrder& tri = getTriangle(border_element_index);
    findTriangleFaceNormal( getNode( tri.vertices[0] ).coords,
                            getNode( tri.vertices[1] ).coords,
                            getNode( tri.vertices[2] ).coords,
                            x, y, z );
};*/

void TetrMeshFirstOrder::build_surface_reverse_lookups()
{
	int i;

	// Clearing
    for( MapIter itr = nodesMap.begin(); itr != nodesMap.end(); ++itr ) {
        int i = itr->first;
        getBorderElementsForNode(i).clear();
    }

    // Filling
    for(i = 0; i < facesNumber; i++)
    {
    	TriangleFirstOrder& tri = getTriangle(i);
        for(int j = 0; j < 3; j++)
        {
        	//CalcNode& node = getNode( tri.vertices[j] );
            //assert( node.isFirstOrder() );
            getBorderElementsForNode(tri.vertices[j]).push_back(i);
        }
    }
}

TriangleFirstOrder& TetrMeshFirstOrder::getTriangle(int index)
{
	assert_ge(index, 0);
	assert_lt(index, borders1.size());
	return borders1[index];
}

TetrahedronFirstOrder& TetrMeshFirstOrder::getTetrByLocalIndex(uint index)
{
	assert_ge(index, 0);
	assert_lt(index, tetrs1.size());
	return tetrs1[index];
}

TetrahedronFirstOrder& TetrMeshFirstOrder::getTetr(uint index)
{
	assert(index >= 0);
	MapIter itr;
    itr = tetrsMap.find(index);
    assert( itr != tetrsMap.end() );
    return tetrs1[itr->second];
}

void TetrMeshFirstOrder::addTetr(TetrahedronFirstOrder& tetr)
{
	if( tetrsNumber == tetrStorageSize )
		createTetrs(tetrStorageSize * STORAGE_ONDEMAND_GROW_RATE);
	assert_lt(tetrsNumber, tetrStorageSize);

	tetrs1.push_back(tetr);
	tetrsMap[tetr.number] = tetrsNumber;
	tetrsNumber++;
}

void TetrMeshFirstOrder::createTetrs(int number)
{
	tetrs1.reserve(number);
	//tetrsMap.reserve(number);
	tetrStorageSize = number;
}

void TetrMeshFirstOrder::addTriangle(TriangleFirstOrder& tri)
{
	if( facesNumber == faceStorageSize )
		createTriangles(faceStorageSize * STORAGE_ONDEMAND_GROW_RATE);
	assert_lt(facesNumber, faceStorageSize);

	borders1.push_back(tri);
	facesNumber++;
}

void TetrMeshFirstOrder::createTriangles(int number)
{
    borders1.reserve(number);
    faceStorageSize = number;
}

int TetrMeshFirstOrder::getTetrsNumber()
{
	return tetrsNumber;
}

int TetrMeshFirstOrder::getTriangleNumber()
{
	return facesNumber;
}

bool TetrMeshFirstOrder::hasTetr(unsigned int index)
{
    MapIter itr;
    itr = tetrsMap.find(index);
    return itr != tetrsMap.end();
}

bool TetrMeshFirstOrder::belongsToTetrahedron(int nodeNum, int tetrNum, int faceNum)
{
    int i1 = (0+faceNum) % 4;
    int i2 = (1+faceNum) % 4;
    int i3 = (2+faceNum) % 4;
    TetrahedronFirstOrder& tetr = getTetr(tetrNum);
    if( (nodeNum == tetr.vertices[i1]) || (nodeNum == tetr.vertices[i2]) || (nodeNum == tetr.vertices[i3]) )
        return true;
    else
        return false;
}

real TetrMeshFirstOrder::tetr_h(int i)
{
    TetrahedronFirstOrder& tetr = getTetr(i);
    return tetrHeight( getNode(tetr.vertices[0]).coords, getNode(tetr.vertices[1]).coords,
                        getNode(tetr.vertices[2]).coords, getNode(tetr.vertices[3]).coords );
};

void TetrMeshFirstOrder::calcMinH()
{
    //assert_gt(tetrsNumber, 0 );
    if( tetrsNumber == 0 )
        return;
    real min_h = tetr_h(tetrsMap.begin()->first);
    assert_gt(min_h, 0 );

    real h;
    // Go through tetrahedrons
    //for(int i = 0; i < tetrsNumber; i++) {
    for( MapIter itr = tetrsMap.begin(); itr != tetrsMap.end(); ++itr ) {
        int i = itr->first;
        TetrahedronFirstOrder& tetr = getTetr(i);
        if ( ( !getNode( tetr.vertices[0] ).isUsed() )
            || ( !getNode( tetr.vertices[1] ).isUsed() )
            || ( !getNode( tetr.vertices[2] ).isUsed() )
            || ( !getNode( tetr.vertices[3] ).isUsed() ) )
            continue;

        // Get current h
        h = tetr_h(i);
        assert(h > 0);
        // Otherwise - just find minimum
        if(h < min_h) { min_h = h; }
    }
    mesh_min_h = min_h;
    if( mesh_min_h < EQUALITY_TOLERANCE )
    {
        //LOG_WARN("Mesh minH is too small: minH " << mesh_min_h << ", FP tolerance: " << EQUALITY_TOLERANCE);
        //LOG_WARN("Fixing it automatically, but it can cause numerous intersting issues");
        mesh_min_h = 10 * EQUALITY_TOLERANCE;
    }
};

real TetrMeshFirstOrder::getMinH()
{
    if( isinf( mesh_min_h ) )
        calcMinH();
    return mesh_min_h;
}

void TetrMeshFirstOrder::calcMaxH()
{
    //assert_gt(tetrsNumber, 0 );
    if( tetrsNumber == 0 )
        return;
    real max_h = tetr_h(tetrsMap.begin()->first);
    assert(max_h > 0 );

    real h;
    // Go through tetrahedrons
    //for(int i = 0; i < tetrsNumber; i++) {
    for( MapIter itr = tetrsMap.begin(); itr != tetrsMap.end(); ++itr ) {
        int i = itr->first;
        TetrahedronFirstOrder& tetr = getTetr(i);
        if ( ( !getNode( tetr.vertices[0] ).isUsed() )
            || ( !getNode( tetr.vertices[1] ).isUsed() )
            || ( !getNode( tetr.vertices[2] ).isUsed() )
            || ( !getNode( tetr.vertices[3] ).isUsed() ) )
            continue;

        // Get current h
        h = tetr_h(i);
        assert(h > 0 );
        // Otherwise - just find minimum
        if(h > max_h) { max_h = h; }
    }
    mesh_max_h = max_h;
};

real TetrMeshFirstOrder::getMaxH()
{
    if( isinf( mesh_max_h ) )
        calcMaxH();
    return mesh_max_h;
}

void TetrMeshFirstOrder::calcMaxEdge()
{
    if( tetrsNumber == 0 )
        return;
    real max_edge = - numeric_limits<float>::infinity();

    std::pair <int, int> combinations[6];
    combinations[0] = make_pair(0, 1);
    combinations[1] = make_pair(0, 2);
    combinations[2] = make_pair(0, 3);
    combinations[3] = make_pair(1, 2);
    combinations[4] = make_pair(1, 3);
    combinations[5] = make_pair(2, 3);

    real edge;
    // Go through tetrahedrons
    for( MapIter itr = tetrsMap.begin(); itr != tetrsMap.end(); ++itr ) {
        int i = itr->first;
        TetrahedronFirstOrder& tetr = getTetr(i);

        for (int j = 0; j < 6; j++) {
            CalcNode& n1 = getNode(tetr.vertices[ combinations[j].first ]);
            CalcNode& n2 = getNode(tetr.vertices[ combinations[j].second ]);

            // Calc current edge
            edge = sqrt((n1.coords - n2.coords) * (n1.coords - n2.coords));
            assert(edge > 0 );
            // Otherwise - just find minimum
            if(edge > max_edge) { max_edge = edge; }
        }
    }

    mesh_max_edge = max_edge;
};

real TetrMeshFirstOrder::getMaxEdge()
{
    if( isinf( mesh_max_edge ) )
        calcMaxEdge();
    return mesh_max_edge;
}

void TetrMeshFirstOrder::calcAvgH()
{
    //assert_gt(tetrsNumber, 0 );
    if( tetrsNumber == 0 )
        return;
    real avg_h = 0;

    real h;
    // Go through tetrahedrons
    //for(int i = 0; i < tetrsNumber; i++) {
    for( MapIter itr = tetrsMap.begin(); itr != tetrsMap.end(); ++itr ) {
        int i = itr->first;
        TetrahedronFirstOrder& tetr = getTetr(i);
        if ( ( !getNode( tetr.vertices[0] ).isUsed() )
            || ( !getNode( tetr.vertices[1] ).isUsed() )
            || ( !getNode( tetr.vertices[2] ).isUsed() )
            || ( !getNode( tetr.vertices[3] ).isUsed() ) )
            continue;

        // Get current h
        h = tetr_h(i);
        assert(h > 0);
        // Otherwise - just find minimum
        avg_h += h;
    }
    mesh_avg_h = avg_h / tetrsNumber;
};

real TetrMeshFirstOrder::getAvgH()
{
    if( isinf( mesh_avg_h ) )
        calcAvgH();
    return mesh_avg_h;
}

void TetrMeshFirstOrder::checkTopology(real tau)
{
}

void TetrMeshFirstOrder::createOutline()
{
}

std::vector<int>& TetrMeshFirstOrder::getVolumeElementsForNode(int index)
{
    // Get local index
    int localIndex = getNodeLocalIndex(index);
    // Resize on demand
    if( localIndex >= volumeElements.size() )
        volumeElements.resize(localIndex + 1);
    return volumeElements[localIndex];
}

std::vector<int>& TetrMeshFirstOrder::getBorderElementsForNode(int index)
{
    // Get local index
    int localIndex = getNodeLocalIndex(index);
    // Resize on demand
    if( localIndex >= borderElements.size() )
        borderElements.resize(localIndex + 1);
    return borderElements[localIndex];
}
