#include "Block.hpp"

void Block::load()
{
	mesh->load();
}

void Block::setModel()
{
	mesh->setModel(model);
}

void Block::doCalc()
{
	solver->calculateMesh(mesh);
}

bool Block::checkTopology()
{
	return mesh->checkTopology();
}
