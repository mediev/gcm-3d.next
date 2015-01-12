#ifndef GCM_RheologyModel_H
#define GCM_RheologyModel_H

#include <string>
#include <vector>

#include "libgcm/util/Logging.hpp"
#include "libgcm/rheologyModels/RheologyMatrix.hpp"
#include "libgcm/rheologyModels/matrixSetters/RheologyMatrixSetter.hpp"
#include "libgcm/rheologyModels/rightHandSideSetters/RightHandSideSetter.hpp"
#include "libgcm/rheologyModels/nodeStateCorrectors/NodeStateCorrector.hpp"
#include "libgcm/solvers/matrixDecomposers/RheologyMatrixDecomposer.hpp"

namespace gcm {

    class RheologyModel {
    public:
        RheologyModel(std::string modelType, uchar nodeType, SetterPtr matrixSetter, DecomposerPtr matrixDecomposer);
        ~RheologyModel();
        std::string getType() const;
        uchar getNodeType() const;
        uchar getSizeOfValuesInPDE() const;
        uchar getSizeOfValuesInODE() const;
        //const RheologyMatrixPtr getRheologyMatrix() const;

        // TODO: does it mean that we create Model for each body?
        // BTW, do we need a concept of 'Body' in new code structure?
        // virtual const Material& getMaterial() const = 0;
        // TODO: how do we identify required node type?
        const SetterPtr getRheologyMatrixSetter() const;
        const DecomposerPtr getRheologyMatrixDecomposer() const;
        virtual const RightHandSideSetter& getRightHandSideSetter() const = 0;
        virtual const std::vector<NodeStateCorrector>& getNodeStateCorrectors() const = 0;

    protected:
        std::string modelType;
        uchar nodeType;
        SetterPtr matrixSetter;
        DecomposerPtr matrixDecomposer;
        //RheologyMatrixPtr rheologyMatrix;

    private:
        USE_LOGGER;
    };
}

#endif