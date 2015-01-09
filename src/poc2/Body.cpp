#include "Body.hpp"

Body::~Body()
{
	if(container != NULL)
		delete[] container;
}

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

void Body::initContainer()
{
	unsigned int s = 0;
	for( std::vector<Block>::iterator it = blocks.begin(); it != blocks.end(); ++it ) 
	{
		assert(it->getModel() != NULL);
		CalcNode tmpNode = newNode(it->getModel()->getNodeType());
		s += tmpNode.getSizeOfVectorInPDE();
		s += tmpNode.getSizeOfValuesInODEs();
	}
	container = new double [NODES_IN_TEST_MESH * s];
	
	for( unsigned char i = 0; i < blocks.size(); i++ ) 
	{
		double* tmpCont = container;
		CalcNode tmpNode = newNode(blocks[i].getModel()->getNodeType());
		blocks[i].initContainer(tmpCont);
		tmpCont += NODES_IN_TEST_MESH * (tmpNode.getSizeOfVectorInPDE() + tmpNode.getSizeOfValuesInODEs());
	}
}

void Body::load(std::vector<CalcNode>& vertices)
{
	initContainer();
	
	for( unsigned char i = 0; i < blocks.size(); i++ ) 
		// Send an vector of nodes with coordinates and start index in vector for every block
		blocks[i].load(vertices, i*8);
	
	bool topology = checkTopology();
	printf("Body: Loaded!\n");
}
