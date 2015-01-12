#include "libgcm/rheologyModels/models/IdealElasticRheologyModel.hpp"
#include "libgcm/rheologyModels/matrixSetters/IsotropicElasticRheologyMatrixSetter.hpp"
#include "libgcm/solvers/matrixDecomposers/IsotropicElasticRheologyMatrixDecomposer.hpp"
#include "libgcm/nodes/IdealElasticNode.hpp"

using namespace gcm;

IdealElasticRheologyModel::IdealElasticRheologyModel()
        : RheologyModel("IdealElasticRheologyModel", IDEAL_ELASTIC_NODE_TYPE, 
                         makeSetterPtr<IsotropicElasticRheologyMatrixSetter>(), 
                         makeDecomposerPtr<IsotropicElasticRheologyMatrixDecomposer>()) {
    
}