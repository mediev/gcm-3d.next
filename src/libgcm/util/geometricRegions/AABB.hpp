#ifndef _GCM_AABB_OUTLINE_H
#define _GCM_AABB_OUTLINE_H  1

#include <limits>

#include "libgcm/nodes/CalcNode.hpp"

// TODO: should we replace it with CubicRegion? (Or make an alias.)
// Does AABB have some unique properties compared with other geometric regions we use?
// We have extra methods in AABB, but they technically can be just migrated to CubucRegion.

namespace gcm {
    class AABB {
    public:
        union {
            real min_coords[3];
            struct {
                real minX;
                real minY;
                real minZ;
            };
        };
        union {
            real max_coords[3];
            struct {
                real maxX;
                real maxY;
                real maxZ;
            };
        };
        AABB();
        AABB( real _minX, real _maxX, real _minY,
		      real _maxY, real _minZ, real _maxZ );
		/**
		 * Change boundary values if vector r exceed them
         */
		void recalculate(const vector3r &r);
		bool isInAABB(const vector3r &r);
/*        bool isInAABB( real x, real y, real z ) const;
        bool isInAABB(const Node* node ) const;
        bool isInAABB(const Node& node) const;
        bool includes( const AABB* box ) const;
        bool includes( const AABB& box ) const;
        //bool intersects( AABB box );
        bool intersects( AABB* box );
        AABB* findIntersection( AABB* box );
        void findIntersection( AABB* box, AABB* intersection );
        void transfer( real x, real y, real z );
		void scale(real x0, real y0, real z0, 
				real scaleX, real scaleY, real scaleZ);
        real getVolume();

        real getDiag() const;
        vector3r getCenter() const;
*/
    };
}

namespace std {
    inline std::ostream& operator<< (std::ostream &os, const gcm::AABB &aabb) {
        os << "[" << aabb.minX << ", " << aabb.maxX << "] ";
        os << "[" << aabb.minY << ", " << aabb.maxY << "] ";
        os << "[" << aabb.minZ << ", " << aabb.maxZ << "] ";
        return os;
    }
}

#endif