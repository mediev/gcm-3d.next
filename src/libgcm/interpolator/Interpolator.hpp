#ifndef GCM_INTERPOLATOR_H
#define GCM_INTERPOLATOR_H

#include <string>

#include "libgcm/Math.hpp"
#include "libgcm/Logging.hpp"

// TODO: signature looks quite bad. We just pass a vector on nodes.
// However, I have no other idea regarding unified interface for interpolator.
// Different interpolators just require different number of nodes and handles them in a different way.
// So, with this approach we just leave this question to each implementation.

namespace gcm {

    class Interpolator {
    public:
        Interpolator();
        ~Interpolator();
        std::string getType();
        virtual void interpolate(CalcNode& curNode, vector<CalcNode>& nodes);
    protected:
        std::string type;
    private:
        USE_LOGGER;
    };
}

#endif