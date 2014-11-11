#ifndef GCM_TRIANGLE_H_
#define GCM_TRIANGLE_H_

#include "libgcm/elem/TetrFirstOrder.hpp"

namespace gcm {
    /*
     * Triangle base class to inherit from.
     */
    class TriangleFirstOrder {
    public:
        TriangleFirstOrder();
        TriangleFirstOrder(uint n, uint v[3]);
        TriangleFirstOrder(uint n, uint v1, uint v2, uint v3);
        /*
         * Number of current tetr
         */
        uint number;
        /*
         * List of tetr vertices.
         */
        uint verts[3];
    };
}
#endif