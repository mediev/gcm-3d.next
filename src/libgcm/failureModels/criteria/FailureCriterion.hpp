#ifndef GCM_FailureCriterion_H
#define GCM_FailureCriterion_H

#include <string>

#include "libgcm/Logging.hpp"
#include "libgcm/node/CalcNode.hpp"


namespace gcm {

    class FailureCriterion {
    public:
        FailureCriterion();
        ~FailureCriterion();
		virtual void checkFailure(CalcNode& node, const float tau) = 0;
    private:
        USE_LOGGER;
    };
}

#endif