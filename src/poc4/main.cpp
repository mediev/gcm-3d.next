#include "nodes.hpp"
#include "models.hpp"
#include "nodes.hpp"
#include "meshes.hpp"
#include "body.hpp"
#include "block.hpp"
#include "solvers.hpp"
#include <iostream>

#define BLOCKS_NUM 2
#define NODES_NUM 3

void testA()
{
	printf("==== Test A ====\n");
	FirstModel model;
	DefaultSolver<FirstNode> solver;
	Body<FirstNode, TetrMesh> body;
	body.load(&solver, &model);
	body.loadBlocks(BLOCKS_NUM, NODES_NUM);
	body.doCalc();
	cout << endl;
}

void testB()
{
	printf("==== Test B ====\n");
	SecondModel model;
	DefaultSolver<SecondNode> solver;
	Body<SecondNode, CubicMesh> body;
	body.load(&solver, &model);
	body.loadBlocks(BLOCKS_NUM, NODES_NUM);
	body.doCalc();
	cout << endl;
}

void testC()
{
	printf("==== Test C ====\n");
	ThirdModel model;
	CustomSolver<ThirdNode> solver;
	Body<ThirdNode, TetrMesh> body;
	body.load(&solver, &model);
	body.loadBlocks(BLOCKS_NUM, NODES_NUM);
	body.doCalc();
	cout << endl;
}

void testD()
{
	printf("==== Test D ====\n");
	FirstModel model1;
	ThirdModel model2;
	DefaultSolver<FirstNode> solver1;
	CustomSolver<ThirdNode> solver2;
	Body<FirstNode, CubicMesh> body1;
	Body<ThirdNode, TetrMesh> body2;
	body1.load(&solver1, &model1);
	body2.load(&solver2, &model2);
	body1.loadBlocks(BLOCKS_NUM, NODES_NUM);
	body2.loadBlocks(BLOCKS_NUM, NODES_NUM);
	body1.doCalc();
	body2.doCalc();
	cout << endl;
}

int main()
{
	testA();
	testB();
	testC();
	testD();
	
	return 0;
}
