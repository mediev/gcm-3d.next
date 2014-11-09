#ifndef GCM_FailedMaterialCorrector_H
#define GCM_FailedMaterialCorrector_H

#include <string>

#include "libgcm/Logging.hpp"
#include "libgcm/node/CalcNode.hpp"


namespace gcm {

    class FailedMaterialCorrector {
    public:
        FailedMaterialCorrector();
        ~FailedMaterialCorrector();
		virtual void applyCorrection(CalcNode& node, const float tau) = 0;
    private:
        USE_LOGGER;
    };
}

#endif