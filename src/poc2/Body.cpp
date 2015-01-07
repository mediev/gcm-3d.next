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

void Body::load()
{
	for(int i = 0; i < bodyConf->blocksNum; i++)
	{
		
		Model* model;
		Solver* solver;
		Mesh* mesh;
		
		if (bodyConf->blocksConf[i].modelType == "modelOne") {
			model = new ModelOne();
		} else if (bodyConf->blocksConf[i].modelType == "modelTwo") {
			model = new ModelTwo();
		} else if (bodyConf->blocksConf[i].modelType == "modelThree") {
			model = new ModelThree();
		}
		
		if (bodyConf->blocksConf[i].solverType == "defaultSolver") {
			solver = new DefaultSolver();
		} else if (bodyConf->blocksConf[i].solverType == "customSolver") {
			solver = new CustomSolver();
		}
		
		if (bodyConf->blocksConf[i].meshType == "tetrMesh") {
			mesh = new TetrMesh();
		} else if (bodyConf->blocksConf[i].meshType == "cubicMesh") {
			mesh = new CubicMesh();
		}
	
		blocks.push_back(Block(bodyConf->blocksConf[i].name, model, solver, mesh));
		blocks[i].setModel();
		blocks[i].load();
	}
	
	bool topology = checkTopology();
	printf("Body: Topology is checked\n");
	printf("Body: Loaded!\n");
}
