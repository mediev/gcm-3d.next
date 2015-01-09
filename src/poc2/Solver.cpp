#include "Solver.hpp"

void Solver::calculateMesh(Mesh* mesh) {
	Model *model = mesh->getModel();
	printf("In solver : Model = %s\n", model->getType().c_str());
	model->getRheologyMatrix()->decompose();
	unsigned int size = mesh->getNodesNumber();
	for (int i = 0; i < size; i++)
		doCalc(mesh->getNode(i));
}

void DefaultSolver::doCalc(CalcNode& node)
{
	assert(node.getType() == DEFAULT_NODE_TYPE);
	DefaultNode& cnode = (DefaultNode&)node;
	// Just test that method exists
	//cnode.getFoo();
	//printf("DefaultSolver: vector size = %d\n", cnode.getSizeOfVectorInPDE());
	
	// Just test coords of vertices
	printf("Coordinates: %f\t%f\t%f\n", node.coords[0], node.coords[1], node.coords[2]);
}

std::string DefaultSolver::getType()
{
	return "DefaultSolver";
}

void CustomSolver::doCalc(CalcNode& node)
{
	assert(node.getType() == CUSTOM_NODE_TYPE
		|| node.getType() == ANOTHER_CUSTOM_NODE_TYPE);
	CustomNode& cnode = (CustomNode&)node;
	// Just test that method exists
	//cnode.getTemperature();
	//printf("CustomSolver: vector size = %d\n", cnode.getSizeOfVectorInPDE());
	
	// Just test coords of vertices
	printf("Coordinates: %f\t%f\t%f\n", node.coords[0], node.coords[1], node.coords[2]);
}

std::string CustomSolver::getType()
{
	return "CustomSolver";
}
