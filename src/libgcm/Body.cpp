#include "Body.hpp"

using namespace gcm;

Body::Body(const BodyProperties& prop) {
	for(auto it = prop.blocks.begin(); it != prop.blocks.end(); it++) {
		Block *block = new Block(*it);
		blocks.push_back(block);
	}
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
