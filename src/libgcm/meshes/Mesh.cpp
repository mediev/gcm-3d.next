#include "libgcm/meshes/Mesh.hpp"


using namespace gcm;
using std::vector;
using std::unordered_map;

Mesh::Mesh() {
	valuesInNodes = NULL;
	movable = false;
	nodeStorageSize = 0;
}

Mesh::~Mesh() {
	if(valuesInNodes != NULL)
		delete[] valuesInNodes;
}

// TODO rename and restructure initializing functions

void Mesh::initNodesWithoutValues(uint numberOfNodes) {
	assert(valuesInNodes == NULL);

	nodes.reserve(numberOfNodes);
	nodesMap.reserve(numberOfNodes);

	nodeStorageSize = numberOfNodes;
}

void Mesh::addNodeWithoutValues(const CalcNode& node) {
	int nodesNum = nodes.size();
	// TODO: What if we need more memory than we reserved
	assert(nodesNum < nodeStorageSize);

	nodes.push_back(node);
	nodesMap[node.number] = nodesNum;
	//outline.recalculate(node.coords);
}

void Mesh::preProcess()
{
	calcMinH();
	preProcessGeometry();
	createOutline();
}

void Mesh::createOutline() {
	uint nodesNumber = nodes.size();

    if (nodesNumber > 0)
    {
        // Create outline
        for(int j = 0; j < 3; j++)
        {
            outline.min_coords[j] = std::numeric_limits<real>::infinity();
            outline.max_coords[j] = - std::numeric_limits<real>::infinity();
        }

        for(uint i = 0; i < nodesNumber; i++)
        {
            CalcNode& node = getNodeByLocalIndex(i);
            if( true /*node.isLocal()*/ )
            {
                for(int j = 0; j < 3; j++) {
                    if(node.coords[j] > outline.max_coords[j])
                        outline.max_coords[j] = node.coords[j];
                    if(node.coords[j] < outline.min_coords[j])
                        outline.min_coords[j] = node.coords[j];
                }
            }
        }
    } else
    {
        //LOG_DEBUG ("Mesh is empty, no outline to create");
    }
}

void Mesh::initValuesInNodes(uint numberOfNodes) {
	// TODO: Does we call this function once?
	assert(valuesInNodes == NULL);

	// Preparing
	assert(rheologyModel != NULL);
	CalcNode tmpNode = newNode(rheologyModel->getNodeType());
	uchar sizeOfValuesInODE = tmpNode.getSizeOfValuesInPDE();
	uchar sizeOfValuesInPDE = tmpNode.getSizeOfValuesInODE();
	printf("Mesh: init container for %d variables per node (both PDE and ODE)\n",
	       sizeOfValuesInODE + sizeOfValuesInPDE);

	// Allocating
	valuesInNodes = new real[numberOfNodes * (sizeOfValuesInODE + sizeOfValuesInPDE)];
	nodes.reserve(numberOfNodes);
	nodesMap.reserve(numberOfNodes);

	nodeStorageSize = numberOfNodes;
}

void Mesh::initValuesInNodes() {
	// TODO: Does we call this function once?
	assert(valuesInNodes == NULL);

	// Preparing
	assert(rheologyModel != NULL);
	CalcNode tmpNode = newNode(rheologyModel->getNodeType());
	uchar sizeOfValuesInODE = tmpNode.getSizeOfValuesInPDE();
	uchar sizeOfValuesInPDE = tmpNode.getSizeOfValuesInODE();
	printf("Mesh: init container for %d variables per node (both PDE and ODE)\n",
	       sizeOfValuesInODE + sizeOfValuesInPDE);

	// Allocating
	valuesInNodes = new real[nodes.size() * (sizeOfValuesInODE + sizeOfValuesInPDE)];
	for(uint i = 0; i < nodes.size(); i++) {
		nodes[i].initMemory(valuesInNodes, nodes.size());
	}
}

void Mesh::addNode(const CalcNode& node)
{
	int nodesNum = nodes.size();
	// TODO: What if we need more memory than we reserved
	assert(nodesNum < nodeStorageSize);

	nodes.push_back(node);
	nodes[nodesNum].initMemory(valuesInNodes, nodesNum);
	nodesMap[node.number] = nodesNum;
	outline.recalculate(node.coords);
}

void Mesh::addNodeIfIsntAlreadyStored(const CalcNode& node) {
	MapIter itr;
	itr = nodesMap.find(node.number);
	if (itr == nodesMap.end())
		addNodeWithoutValues(node);
	outline.recalculate(node.coords);
}

CalcNode& Mesh::getNode(uint index)
{
	assert(index >= 0);
	MapIter itr;
	itr = nodesMap.find(index);
	assert_false(itr != nodesMap.end());
	return nodes[itr->second];
}

CalcNode& Mesh::getNodeByLocalIndex(uint index)
{
	assert(index >= 0);
	assert(index < nodes.size());
	return nodes[index];
}

uint Mesh::getNodeLocalIndex(uint index) const
{
	assert_ge(index, 0);
	MapIter itr;
	itr = nodesMap.find(index);
	return ( itr != nodesMap.end() ? itr->second : -1 );
}

uint Mesh::getNodesNumber()
{
	return nodes.size();
}

void Mesh::setRheologyModel(RheologyModel* _rheologyModel) {
	rheologyModel = _rheologyModel;
}

RheologyModel* Mesh::getRheologyModel() {
	return rheologyModel;
}

std::string Mesh::getType() {
	return type;
}

AABB Mesh::getOutline() {
	return outline;
}

bool Mesh::hasNode(int index)
{
	assert_ge(index, 0);
	MapIter itr;
	itr = nodesMap.find(index);
	return itr != nodesMap.end();
}

void Mesh::setId(std::string _id)
{
	id = _id;
}

std::string Mesh::getId() const
{
	return id;
}

std::string Mesh::snapshot(int number)
{
    return getSnaphotter().dump(this, number);
}
