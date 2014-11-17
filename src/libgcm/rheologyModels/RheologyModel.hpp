#ifndef GCM_RheologyModel_H
#define GCM_RheologyModel_H

#include <string>

#include "libgcm/Logging.hpp"

#include "libgcm/node/CalcNode.hpp"

#include "libgcm/failureModels/FailureModel.hpp"
#include "libgcm/failureModels/NoFailureModel.hpp"
#include "libgcm/failureModels/CrackFailureModel.hpp"
#include "libgcm/failureModels/ScalarFailureModel.hpp"
#include "libgcm/failureModels/ContinualFailureModel.hpp"
#include "libgcm/failureModels/DebugFailureModel.hpp"
#include "libgcm/failureModels/HashinFailureModel.hpp"
#include "libgcm/failureModels/TsaiHillFailureModel.hpp"
#include "libgcm/failureModels/TsaiWuFailureModel.hpp"
#include "libgcm/failureModels/DruckerPragerFailureModel.hpp"
#include "libgcm/failureModels/PuckFailureModel.hpp"

#include "libgcm/rheologyModels/Material.hpp"


namespace gcm {

    class RheologyModel {
    public:
        RheologyModel();
        ~RheologyModel();
        std::string getType();
		/**
		 * Number of values to calculate
		 */
		int valNum;
		/**
		 * Number of values who eigenvalue is equil to zero
		 */
		int zeroNum;
		
        // TODO: is it possible to make all these entities singletons?
        // It's not clear if they have internal state or are completely stateless.

        // TODO: does it mean that we create Model for each body?
        // BTW, do we need a concept of 'Body' in new code structure?
        virtual const Material& getMaterial() const = 0;
        // TODO: how do we identify required node type?
        virtual const RheologyMatrixSetter& getRheologyMatrixSetter() const = 0;
        virtual const RightHandSideSetter& getRightHandSideSetter() const = 0;
        virtual const vector<NodeStateCorrector>& getNodeStateCorrectors() const = 0;
    protected:
    private:
        USE_LOGGER;
    };
}

#endif
