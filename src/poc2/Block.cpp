#include "Block.hpp"

void Block::load(std::vector<CalcNode>& vertices, unsigned char indx)
{
	mesh->load(vertices, indx);
}

void Block::setModel()
{
	mesh->setModel(model);
}

Model* Block::getModel()
{
	return model;
}

void Block::doCalc()
{
	solver->calculateMesh(mesh);
}

bool Block::checkTopology()
{
	return mesh->checkTopology();
}
