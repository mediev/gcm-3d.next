#include "libgcm/util/geometricRegions/AABB.hpp"


using namespace gcm;
using std::numeric_limits;

AABB::AABB(){
	minX = minY = minZ = numeric_limits<float>::infinity();
    maxX = maxY = maxZ = - numeric_limits<float>::infinity();
}

AABB::AABB(real _minX, real _maxX, real _minY, 
           real _maxY, real _minZ, real _maxZ) {
	minX = _minX;
    minY = _minY;
    minZ = _minZ;
    maxX = _maxX;
    maxY = _maxY;
    maxZ = _maxZ;
}

void AABB::recalculate(const vector3r &r) {
	minX = (minX > r.x) ? r.x : minX;
	minY = (minY > r.y) ? r.y : minY;
	minZ = (minZ > r.z) ? r.z : minZ;
	maxX = (maxX < r.x) ? r.x : maxX;
	maxY = (maxY < r.y) ? r.y : maxY;
	maxZ = (maxZ < r.z) ? r.z : maxZ;
}

bool AABB::isInAABB(const vector3r& r) {
	return ( (r.x <= maxX) && (r.x >= minX) &&
	         (r.y <= maxY) && (r.y >= minY) &&
	         (r.z <= maxZ) && (r.z >= minZ) );
}
