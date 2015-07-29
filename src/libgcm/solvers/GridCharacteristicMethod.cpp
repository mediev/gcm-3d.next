#include "libgcm/solvers/GridCharacteristicMethod.hpp"

using namespace gcm;

void GridCharacteristicMethod::doNextTimeStep(Mesh* mesh) {
	std::cout << "GridCharacteristicMethod::doNextTimeStep\n";
	assert_eq(mesh->nodeStorageSize, mesh->nodes.size());
	assert_eq(mesh->nodeStorageSize, mesh->newNodes.size());
	for(uint i = 0; i < mesh->nodes.size(); i++) {
		CalcNode& node = mesh->nodes[i];
		CalcNode& newnode = mesh->newNodes[i];
	
		assert_eq(node.getSizeOfValuesInODE(), newnode.getSizeOfValuesInODE());
		assert_eq(node.getSizeOfValuesInPDE(), newnode.getSizeOfValuesInPDE());
		
		for(int j = 0; j < node.getSizeOfValuesInPDE(); j++)
			newnode.valuesInPDE[j] = node.valuesInPDE[j];
		
		for(int j = 0; j < node.getSizeOfValuesInODE(); j++)
			newnode.valuesInODE[j] = node.valuesInODE[j];
		
		newnode.coords = node.coords;
		
	}
}
