#ifndef _GCM_Region_H
#define _GCM_Region_H 1

#include "libgcm/node/Node.hpp"


namespace gcm {
    class Region
    {
    public:
        Region();
        virtual ~Region() = 0;
        virtual bool contains( Node& node ) = 0;
    };
}

#endif