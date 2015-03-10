#include "libgcm/nodes/CalcNode.hpp"
#include "libgcm/util/Assertion.hpp"

using namespace gcm;
using std::copy;

CalcNode::CalcNode(uchar sizeOfValuesInPDE,
                   uchar sizeOfValuesInODE,
                   uchar nodeType) :
                   sizeOfValuesInPDE(sizeOfValuesInPDE), 
                   sizeOfValuesInODE(sizeOfValuesInODE),
                   nodeType(nodeType)
{
}

CalcNode::~CalcNode()
{
    // No delete[] calls here, since we use placement new 
}

void CalcNode::clear() {
	memset(valuesInPDE, 0, sizeOfValuesInPDE * sizeof (gcm::real));
	memset(valuesInODE, 0, sizeOfValuesInODE * sizeof (gcm::real));
}

void CalcNode::initMemory(real *buffer, int nodeNum) {
    real* startAddr = buffer + nodeNum * (sizeOfValuesInPDE + sizeOfValuesInODE);
    valuesInPDE = new (startAddr) real[sizeOfValuesInPDE];
    valuesInODE = new (startAddr + sizeOfValuesInPDE) real[sizeOfValuesInODE];
}


void CalcNode::operator=(const CalcNode& orig) {
    assert_true(nodeType == orig.nodeType);
    assert_true(sizeOfValuesInPDE == orig.sizeOfValuesInPDE);
    assert_true(sizeOfValuesInODE = orig.sizeOfValuesInODE);
    assert_true(valuesInPDE != NULL);
    assert_true(valuesInODE != NULL);
    publicFlags = orig.publicFlags;
    errorFlags = orig.errorFlags;
    borderConditionId = orig.borderConditionId;
    contactConditionId = orig.contactConditionId;
    bodyId = orig.bodyId;
    materialId = orig.materialId;
    rheologyMatrix = orig.rheologyMatrix;
    number = orig.number;
    coords = orig.coords;
    for (int i = 0; i < sizeOfValuesInPDE; i++)
        valuesInPDE[i] = orig.valuesInPDE[i];
    for (int i = 0; i < sizeOfValuesInODE; i++)
        valuesInODE[i] = orig.valuesInODE[i];
}

uchar CalcNode::getType() const
{
    return nodeType;
}

uchar CalcNode::getSizeOfValuesInPDE() const
{
    return sizeOfValuesInPDE;
}

uchar CalcNode::getSizeOfValuesInODE() const
{
    return sizeOfValuesInODE;
}

uchar CalcNode::getPublicFlags() const
{
    return publicFlags.flags;
}

void CalcNode::setPublicFlags(uchar flags)
{
    publicFlags.flags = flags;
}

uchar CalcNode::getErrorFlags() const
{
    return errorFlags.flags;
}

void CalcNode::setErrorFlags(uchar flags)
{
    errorFlags.flags = flags;
}

void CalcNode::setBorderConditionId(uchar newBorderCondId)
{
    borderConditionId = newBorderCondId;
}

uchar CalcNode::getBorderConditionId() const
{
    return borderConditionId;
}

void CalcNode::setContactConditionId(uchar newContactConditionId)
{
    contactConditionId = newContactConditionId;
}

uchar CalcNode::getContactConditionId() const
{
    return contactConditionId;
}

void CalcNode::setMaterialId(uchar id)
{
    materialId = id;
    //rho = Engine::getInstance().getMaterial(id)->getRho();
}

uchar CalcNode::getMaterialId() const
{
    return materialId;
}

void CalcNode::setRheologyMatrix(RheologyMatrixPtr matrix)
{
    assert_true(matrix.get());
    rheologyMatrix = matrix;
}

RheologyMatrixPtr CalcNode::getRheologyMatrix() const
{
    return rheologyMatrix;
}

/*MaterialPtr CalcNode::getMaterial() const
{
    return Engine::getInstance().getMaterial(materialId);
}*/

bool CalcNode::isUsed() const
{
    return publicFlags.isUsed;
}

void CalcNode::setUsed(bool value)
{
    publicFlags.isUsed = value;
}

bool CalcNode::isHighOrder() const
{
    return publicFlags.isHighOrder == 0;
}

void CalcNode::setHighOrder(bool value)
{
    publicFlags.isHighOrder = value;
}

bool CalcNode::isVirtual() const
{
    return publicFlags.isVirtual;
}

void CalcNode::setVirtual(bool value)
{
    publicFlags.isVirtual = value;
}

bool CalcNode::isBorder() const
{
    return publicFlags.isBorder;
}

bool CalcNode::isInner() const
{
    return !isBorder();
}

void CalcNode::setBorder(bool value)
{
    publicFlags.isBorder = value;
}


bool CalcNode::isInContact() const
{
    return publicFlags.isInContact;
}

void CalcNode::setInContact(bool value)
{
    publicFlags.isInContact = value;
}

bool CalcNode::isDestroyed() const
{
    return publicFlags.isDestroyed;
}

void CalcNode::setDestroyed(bool value)
{
    publicFlags.isDestroyed = value;
}

bool CalcNode::isContactDestroyed() const
{
    return publicFlags.isContactDestroyed;
}

void CalcNode::setContactDestroyed(bool value)
{
    publicFlags.isContactDestroyed = value;
}

bool CalcNode::getCustomFlag(uchar flag) const
{
    switch (flag) {
    case FLAG_1: return publicFlags.customFlag1;
    default: THROW_INVALID_ARG("Invalid flag specified");
    }
}

void CalcNode::setCustomFlag(uchar flag, bool value)
{
    switch (flag) {
    case FLAG_1: publicFlags.customFlag1 = value; break;
    default: THROW_INVALID_ARG("Invalid flag specified");
    }
}

void CalcNode::setBadNeighborsX()
{
    errorFlags.badNeighborsX = true;
}

void CalcNode::setBadNeighborsY()
{
    errorFlags.badNeighborsY = true;
}

void CalcNode::setBadNeighborsZ()
{
    errorFlags.badNeighborsZ = true;
}

void CalcNode::setBadOuterNormal()
{
    errorFlags.badOuterNormal = true;
}

void CalcNode::setBadNeighbors(unsigned int axisNum)
{
    switch (axisNum) {
    case 0: setBadNeighborsX();
        break;
    case 1: setBadNeighborsY();
        break;
    case 2: setBadNeighborsZ();
        break;
    default: THROW_INVALID_ARG("Invalid axis number specified");
    }
}

void CalcNode::clearErrorFlags()
{
    errorFlags.flags = 0;
}