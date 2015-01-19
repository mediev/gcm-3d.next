#include "Body.hpp"

using namespace gcm;

void Body::doCalc()
{
	for( auto it = blocks.begin(); it != blocks.end(); ++it )
		it->doNextTimeStep();
}

bool Body::checkTopology()
{
	for( auto it = blocks.begin(); it != blocks.end(); ++it ) {
		real tau = 0;
		it->checkTopology(tau);
	}
	return true;
}

void Body::addBlock(Block block)
{
	blocks.push_back(block);	
}

void Body::setRheologyModel(unsigned char i)
{
	blocks[i].setRheologyModel();
}

void Body::load(std::vector<CalcNode>& vertices)
{	
	for( unsigned char i = 0; i < blocks.size(); i++ ) {
		// Send an vector of nodes with coordinates and start index in vector for every block
		blocks[i].load(vertices, i*8);
	}
	
	checkTopology();
	printf("Body: Loaded!\n");
}
