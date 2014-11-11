#ifndef GCM_FailureModel_H
#define GCM_FailureModel_H

#include <string>

#include "libgcm/Logging.hpp"

#include "libgcm/node/CalcNode.hpp"
#include "libgcm/failure/criteria/FailureCriterion.hpp"
#include "libgcm/failure/correctors/FailedMaterialCorrector.hpp"


namespace gcm {

    class FailureModel {
    public:
        FailureModel();
        ~FailureModel();
        std::string getType();
		void checkFailure(CalcNode& node, const float tau);
		void applyCorrection(CalcNode& node, const float tau);
    protected:
        std::string type;
		std::vector<FailureCriterion*> criteria;
		std::vector<FailedMaterialCorrector*> correctors;
    private:
        USE_LOGGER;
    };
}

#endif