#include "Block.hpp"

using namespace gcm;

void Block::load(std::vector<CalcNode>& vertices, unsigned char indx)
{
	mesh->load(vertices, indx);
}

void Block::setRheologyModel()
{
	mesh->setRheologyModel(model);
}

RheologyModel* Block::getRheologyModel()
{
	return model;
}

void Block::doNextTimeStep()
{
	solver->doNextTimeStep(mesh);
}

void Block::checkTopology(real tau)
{
	mesh->checkTopology(tau);
}
