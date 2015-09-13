#include "libgcm/meshes/Mesh.hpp"
#include "libgcm/Engine.hpp"

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
			for(int i = 0; i < node->getSizeOfPDE(); i++)
				node->PDE[i] = valuesInPDE[i];
		} else {
			for(int i = 0; i < node->getSizeOfPDE(); i++)
				node->PDE[i] = 0;
		}
	}
	for(auto node = nodes.begin(); node != nodes.end(); node++) {
		for(int i = 0; i < node->getSizeOfODE(); i++)
			node->ODE[i] = 0;
	}
	
	for(auto newnode = newNodes.begin(); newnode != newNodes.end(); newnode++) {
		for(int i = 0; i < newnode->getSizeOfODE(); i++)
			newnode->ODE[i] = 0;
		for(int i = 0; i < newnode->getSizeOfPDE(); i++)
			newnode->PDE[i] = 0;
	}
}

void Mesh::setMaterial(const MaterialPtr& material, const AABB& area) {
	assert_eq(nodes.size(), newNodes.size());
	int size = rheologyModel->getSizeOfValuesInPDE();
	SetterPtr setter = rheologyModel->getRheologyMatrixSetter();
	DecomposerPtr decomposer = rheologyModel->getRheologyMatrixDecomposer();
	for(uint i = 0; i < nodes.size(); i++)
		if( area.isInAABB(nodes[i].coords) ) {
			nodes[i].setRheologyMatrix(makeRheologyMatrixPtr(size, material, 
			                                                 setter, decomposer));
			newNodes[i].setRheologyMatrix(makeRheologyMatrixPtr(size, material, 
			                                                 setter, decomposer));
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
	CalcNode tmpNode = getNewNode(rheologyModel->getNodeType());
	uchar sizeOfValuesInODE = tmpNode.getSizeOfODE();
	uchar sizeOfValuesInPDE = tmpNode.getSizeOfPDE();
	printf("Mesh: init container for %d variables per node (both PDE and ODE)\n",
	       sizeOfValuesInODE + sizeOfValuesInPDE);

	// Allocating
	
	valuesInNodes = new real[nodes.size() * (sizeOfValuesInODE + sizeOfValuesInPDE)];
	for(uint i = 0; i < nodes.size(); i++) {
		nodes[i].initMemory(valuesInNodes, i);
	}
	valuesInNewNodes = new real[newNodes.size() * (sizeOfValuesInODE + sizeOfValuesInPDE)];
	for(uint i = 0; i < newNodes.size(); i++) {
		newNodes[i].initMemory(valuesInNewNodes, i);
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

void Mesh::stageX() {
	std::cout << "Mesh::stageX\n";
	assert_eq(nodeStorageSize, nodes.size());
	assert_eq(nodeStorageSize, newNodes.size());
	real* dksi = new real [rheologyModel->getSizeOfValuesInPDE()];
	real* RiemannSolvers = new real [rheologyModel->getSizeOfValuesInPDE()];
	real tau = Engine::getInstance().getTimeStep();
	for (uint itr = 0; itr < nodes.size(); itr++) {
		CalcNode& node = nodes[itr];
		CalcNode& newnode = newNodes[itr];
		assert_eq(node.getSizeOfPDE(), newnode.getSizeOfPDE());

		if (!node.isBorder()) { // inner nodes
			RheologyMatrixPtr matrix = node.getRheologyMatrix();
			matrix->decomposeX(node);

			for (int j = 0; j < node.getSizeOfPDE(); j++) {
				dksi[j] = -matrix->getL(j, j) * tau;
				vector3r dx(dksi[j], 0, 0);
				
				CalcNode nodeForInterpolation = nodes[itr];
				nodeForInterpolation.coords += dx;
				interpolateNode(nodeForInterpolation);
				
				RiemannSolvers[j] = 0;
				for(int i = 0; i < node.getSizeOfPDE(); i++) {
					RiemannSolvers[j] += matrix->getU(j, i) * nodeForInterpolation.PDE[i];
				}	
			}

			newnode = node;			
			for(int i = 0; i < node.getSizeOfPDE(); i++) {
				newnode.PDE[i] = 0;
				for(int j = 0; j < node.getSizeOfPDE(); j++)
					newnode.PDE[i] += matrix->getU1(i, j) * RiemannSolvers[j];
			}
			
		} else { // border nodes
			for (int j = 0; j < node.getSizeOfPDE(); j++) {
				newnode.PDE[j] = 0;
			}

		}
	}

	delete [] dksi;
	delete [] RiemannSolvers;
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
    return getSnapshotter().dump(this, number);
}
