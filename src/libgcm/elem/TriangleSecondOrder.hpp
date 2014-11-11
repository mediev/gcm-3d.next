#ifndef GCM_TRIANGLE_SECOND_ORDER_H_
#define GCM_TRIANGLE_SECOND_ORDER_H_

#include "libgcm/elem/TriangleFirstOrder.hpp"

namespace gcm {
    /*
     * Triangle base class to inherit from.
     */
    class TriangleSecondOrder : public TriangleFirstOrder {
    public:
        TriangleSecondOrder();
        TriangleSecondOrder(uint n, uint v[3]);
        TriangleSecondOrder(uint n, uint v[3], uint av[3]);
        /*
         * List of additional vertices on edges
         */
        uint addVerts[3];
    };
}
#endif