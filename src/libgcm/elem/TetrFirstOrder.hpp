#ifndef GCM_TETR_H_
#define GCM_TETR_H_

#include <iostream>


namespace gcm {
    /*
     * Tetrahedron base class to inherit from.
     */
    class TetrFirstOrder {
    public:
        TetrFirstOrder();
        TetrFirstOrder(uint n, uint v[4]);
        /*
         * Number of current tetr
         */
        uint number;
        /*
         * List of tetr vertices.
         */
        uint verts[4];
    };
}

namespace std {
    inline std::ostream& operator<< (std::ostream &os, const gcm::TetrFirstOrder &tetr) {
        os << "\n\tTetr number: " << tetr.number << "\n";
        os << "\tVerts:";
        for( uint i = 0; i < 4; i++ )
            os << " " << tetr.verts[i];
        return os;
    }
}

#endif