#include "Body.hpp"

using namespace gcm;

Body::Body() {
}

void Body::loadTask(const BodyProperties& prop) {
	printf("Loading task in body %d\n", id);
	for(uint i = 0; i < prop.blocks.size(); i++) {
		Block *block = new Block();
		block->setId(prop.blocks[i].id);
		blocks.push_back(block);
	}
	for(uint i = 0; i < prop.blocks.size(); i++)
		blocks[i]->loadTask(prop.blocks[i]);
}

void Body::doNextTimeStep()
{
	for( auto it = blocks.begin(); it != blocks.end(); ++it )
		(*it)->doNextTimeStep();
}

void Body::checkTopology()
{
	for( auto it = blocks.begin(); it != blocks.end(); ++it ) {
		real tau = 0;
		(*it)->checkTopology(tau);
	}
}

void Body::setId(uint _id) {
	id = _id;
}

uint Body::getId() {
	return id;
}

