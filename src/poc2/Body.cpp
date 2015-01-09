#include "Body.hpp"

void Body::doCalc()
{
	for( std::vector<Block>::iterator it = blocks.begin(); it != blocks.end(); ++it )
		it->doCalc();
}

bool Body::checkTopology()
{
	for( std::vector<Block>::iterator it = blocks.begin(); it != blocks.end(); ++it )
		it->checkTopology();
		
	return true;
}

void Body::addBlock(Block block)
{
	blocks.push_back(block);	
}

void Body::setModel(unsigned char i)
{
	blocks[i].setModel();
}

void Body::load(std::vector<CalcNode>& vertices)
{	
	for( unsigned char i = 0; i < blocks.size(); i++ ) {
		// Send an vector of nodes with coordinates and start index in vector for every block
		blocks[i].load(vertices, i*8);
	}
	
	bool topology = checkTopology();
	printf("Body: Loaded!\n");
}
