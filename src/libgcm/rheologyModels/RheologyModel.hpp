#ifndef GCM_RheologyModel_H
#define GCM_RheologyModel_H

#include <string>

#include "libgcm/Logging.hpp"

#include "libgcm/node/CalcNode.hpp"


namespace gcm {

    class RheologyModel {
    public:
        RheologyModel();
        ~RheologyModel();
        std::string getType();
        
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