#include "libgcm/solvers/GridCharacteristicMethod.hpp"

using namespace gcm;

void GridCharacteristicMethod::stageX(Mesh* mesh) {
	std::cout << "GridCharacteristicMethod::stageX\n";
	assert_eq(mesh->nodeStorageSize, mesh->nodes.size());
	assert_eq(mesh->nodeStorageSize, mesh->newNodes.size());
	for(uint itr = 0; itr < mesh->nodes.size(); itr++) {
		CalcNode& node = mesh->nodes[itr];
		CalcNode& newnode = mesh->newNodes[itr];			
		assert_eq(node.getSizeOfValuesInPDE(), newnode.getSizeOfValuesInPDE());
		
		if( !node.isBorder() ) { // inner nodes
			RheologyMatrixPtr matrix = node.getRheologyMatrix();
			matrix->decomposeX(node);
			
			for(int j = 0; j < node.getSizeOfValuesInPDE(); j++) {
				newnode.valuesInPDE[j] = node.valuesInPDE[j];
			}
			
		} else { // border nodes
			for(int j = 0; j < node.getSizeOfValuesInPDE(); j++) {
				newnode.valuesInPDE[j] = 0;
			}
			
		}
	}
}