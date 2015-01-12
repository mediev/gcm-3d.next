#include "libgcm/rheologyModels/RheologyModel.hpp"
#include "libgcm/util/NodeTypes.hpp"
#include "libgcm/util/Assertion.hpp"

using namespace gcm;

RheologyModel::RheologyModel(std::string modelType, uchar nodeType, SetterPtr matrixSetter, DecomposerPtr matrixDecomposer)
        : modelType(modelType), nodeType(nodeType), matrixSetter(matrixSetter), matrixDecomposer(matrixDecomposer)
{
}

std::string RheologyModel::getType() const {
    return modelType;
}

const SetterPtr RheologyModel::getRheologyMatrixSetter() const {
    return matrixSetter;
}

const DecomposerPtr RheologyModel::getRheologyMatrixDecomposer() const {
    return matrixDecomposer;
}

uchar RheologyModel::getNodeType() const {
    return nodeType;
}

uchar RheologyModel::getSizeOfValuesInPDE() const {
    CalcNode tmpNode = newNode(nodeType);
    return tmpNode.getSizeOfValuesInPDE();
}

uchar RheologyModel::getSizeOfValuesInODE() const {
    CalcNode tmpNode = newNode(nodeType);
    return tmpNode.getSizeOfValuesInODE();
}