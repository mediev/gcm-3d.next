#include "libgcm/meshes/Mesh.hpp"


using namespace gcm;
using std::vector;
using std::unordered_map;

Mesh::Mesh() {
	valuesInNodes = NULL;
	valuesInNewNodes = NULL;
	movable = false;
	nodeStorageSize = 0;
}

Mesh::~Mesh() {
	if(valuesInNodes != NULL)
		delete[] valuesInNodes;
		
	if(valuesInNewNodes != NULL)
		delete[] valuesInNewNodes;
}

// TODO rename and restructure initializing functions

void Mesh::initNodesWithoutValues(uint numberOfNodes) {
	assert(valuesInNodes == NULL);
	assert(valuesInNewNodes == NULL);

	nodes.reserve(numberOfNodes);
	newNodes.reserve(numberOfNodes);
	nodesMap.reserve(numberOfNodes);

	nodeStorageSize = numberOfNodes;
}

void Mesh::addNodeWithoutValues(const CalcNode& node) {
	uint nodesNum = nodes.size();
	// TODO: What if we need more memory than we reserved
	assert(nodesNum < nodeStorageSize);
	assert_eq(nodes.size(), newNodes.size());

	nodes.push_back(node);
	newNodes.push_back(node);
	nodesMap[node.number] = nodesNum;
	outline.recalculate(node.coords);
}

void Mesh::replaceNewAndCurrentNodes() {
	std::vector<CalcNode> tmp = nodes;
	nodes = newNodes;
	newNodes = tmp;
}

void Mesh::setInitialState(const real* valuesInPDE, const AABB& area) {
	for(auto node = nodes.begin(); node != nodes.end(); node++) {
		if (area.isInAABB(node->coords)) {
			for(int i = 0; i < node->getSizeOfValuesInPDE(); i++)
				node->valuesInPDE[i] = valuesInPDE[i];
		} else {
			for(int i = 0; i < node->getSizeOfValuesInPDE(); i++)
				node->valuesInPDE[i] = 0;
		}
	}
	for(auto node = nodes.begin(); node != nodes.end(); node++) {
		for(int i = 0; i < node->getSizeOfValuesInODE(); i++)
			node->valuesInODE[i] = 0;
	}
	
	for(auto newNode = newNodes.begin(); newNode != newNodes.end(); newNode++) {
		for(int i = 0; i < newNode->getSizeOfValuesInODE(); i++)
			newNode->valuesInODE[i] = 0;
		for(int i = 0; i < newNode->getSizeOfValuesInPDE(); i++)
			newNode->valuesInPDE[i] = 0;
	}
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

void Mesh::initValuesInNodes() {
	// TODO: Does we call this function once?
	assert(valuesInNodes == NULL);
	assert(valuesInNewNodes == NULL);
	assert_eq(nodes.size(), newNodes.size());
	
	// Preparing
	assert(rheologyModel != NULL);
	CalcNode tmpNode = newNode(rheologyModel->getNodeType());
	uchar sizeOfValuesInODE = tmpNode.getSizeOfValuesInODE();
	uchar sizeOfValuesInPDE = tmpNode.getSizeOfValuesInPDE();
	printf("Mesh: init container for %d variables per node (both PDE and ODE)\n",
	       sizeOfValuesInODE + sizeOfValuesInPDE);

	// Allocating
	
	valuesInNodes = new real[nodes.size() * 2 * (sizeOfValuesInODE + sizeOfValuesInPDE)];
	for(uint i = 0; i < nodes.size(); i++) {
		nodes[i].initMemory(valuesInNodes, nodes.size());
	}
	valuesInNewNodes = new real[newNodes.size() * 2 * (sizeOfValuesInODE + sizeOfValuesInPDE)];
	for(uint i = 0; i < newNodes.size(); i++) {
		newNodes[i].initMemory(valuesInNewNodes, newNodes.size());
	}
}

void Mesh::addNode(const CalcNode& node)
{
	uint nodesNum = nodes.size();
	// TODO: What if we need more memory than we reserved
	assert(nodesNum < nodeStorageSize);
	assert_eq(nodes.size(), newNodes.size());

	nodes.push_back(node);
	newNodes.push_back(node);
	nodes[nodesNum].initMemory(valuesInNodes, nodesNum);
	newNodes[nodesNum].initMemory(valuesInNewNodes, nodesNum);
	nodesMap[node.number] = nodesNum;
	outline.recalculate(node.coords);
}

CalcNode& Mesh::getNode(uint index)
{
	assert_ge(index, 0);
	MapIter itr;
	itr = nodesMap.find(index);
	assert_ne(itr, nodesMap.end());
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
	assert_eq(nodes.size(), newNodes.size());
	assert_eq(nodeStorageSize, nodes.size());
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

void Mesh::setId(uint _id)
{
	id = _id;
}

uint Mesh::getId() const
{
	return id;
}

void Mesh::setRank(int _rank) {
	rank = _rank;
}

int Mesh::getRank() const {
	return rank;
}

std::string Mesh::snapshot(int number)
{
    return getSnaphotter().dump(this, number);
}
