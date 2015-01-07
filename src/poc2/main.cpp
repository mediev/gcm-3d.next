#include "Body.hpp"
#include "Block.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "Solver.hpp"

#define BLOCKS_IN_TEST_BODY 3

Body loadBody(std::string modelType, std::string solverType, unsigned char blocksNum) {
	
	BodyConfig* bodyConf = new BodyConfig(blocksNum);
	
	if(blocksNum > 0)
	{
		// First block
		bodyConf->blocksConf[0].name = "firstBlock";
		bodyConf->blocksConf[0].modelType = modelType;
		bodyConf->blocksConf[0].solverType = solverType;
		bodyConf->blocksConf[0].meshType = "tetrMesh";
		// Bottom
		bodyConf->blocksConf[0].vertices[0].x = 0.0;
		bodyConf->blocksConf[0].vertices[0].y = 0.0;
		bodyConf->blocksConf[0].vertices[0].z = 0.0;
		bodyConf->blocksConf[0].vertices[1].x = 0.0;
		bodyConf->blocksConf[0].vertices[1].y = 1.0;
		bodyConf->blocksConf[0].vertices[1].z = 0.0;
		bodyConf->blocksConf[0].vertices[2].x = 0.33;
		bodyConf->blocksConf[0].vertices[2].y = 1.0;
		bodyConf->blocksConf[0].vertices[2].z = 0.0;
		bodyConf->blocksConf[0].vertices[3].x = 0.33;
		bodyConf->blocksConf[0].vertices[3].y = 0.0;
		bodyConf->blocksConf[0].vertices[3].z = 0.0;
		// Top
		bodyConf->blocksConf[0].vertices[4].x = 0.0;
		bodyConf->blocksConf[0].vertices[4].y = 0.0;
		bodyConf->blocksConf[0].vertices[4].z = 1.0;
		bodyConf->blocksConf[0].vertices[5].x = 0.0;
		bodyConf->blocksConf[0].vertices[5].y = 1.0;
		bodyConf->blocksConf[0].vertices[5].z = 1.0;
		bodyConf->blocksConf[0].vertices[6].x = 0.33;
		bodyConf->blocksConf[0].vertices[6].y = 1.0;
		bodyConf->blocksConf[0].vertices[6].z = 1.0;
		bodyConf->blocksConf[0].vertices[7].x = 0.33;
		bodyConf->blocksConf[0].vertices[7].y = 0.0;
		bodyConf->blocksConf[0].vertices[7].z = 1.0;
	}
	
	if(blocksNum > 1)
	{
		// Second block
		bodyConf->blocksConf[1].name = "secondBlock";
		bodyConf->blocksConf[1].modelType = "modelTwo";
		bodyConf->blocksConf[1].solverType = "customSolver";
		bodyConf->blocksConf[1].meshType = "cubicMesh";
		// Bottom
		bodyConf->blocksConf[1].vertices[0].x = 0.33;
		bodyConf->blocksConf[1].vertices[0].y = 0.0;
		bodyConf->blocksConf[1].vertices[0].z = 0.0;
		bodyConf->blocksConf[1].vertices[1].x = 0.33;
		bodyConf->blocksConf[1].vertices[1].y = 1.0;
		bodyConf->blocksConf[1].vertices[1].z = 0.0;
		bodyConf->blocksConf[1].vertices[2].x = 0.66;
		bodyConf->blocksConf[1].vertices[2].y = 1.0;
		bodyConf->blocksConf[1].vertices[2].z = 0.0;
		bodyConf->blocksConf[1].vertices[3].x = 0.66;
		bodyConf->blocksConf[1].vertices[3].y = 0.0;
		bodyConf->blocksConf[1].vertices[3].z = 0.0;
		// Top
		bodyConf->blocksConf[1].vertices[4].x = 0.33;
		bodyConf->blocksConf[1].vertices[4].y = 0.0;
		bodyConf->blocksConf[1].vertices[4].z = 1.0;
		bodyConf->blocksConf[1].vertices[5].x = 0.33;
		bodyConf->blocksConf[1].vertices[5].y = 1.0;
		bodyConf->blocksConf[1].vertices[5].z = 1.0;
		bodyConf->blocksConf[1].vertices[6].x = 0.66;
		bodyConf->blocksConf[1].vertices[6].y = 1.0;
		bodyConf->blocksConf[1].vertices[6].z = 1.0;
		bodyConf->blocksConf[1].vertices[7].x = 0.66;
		bodyConf->blocksConf[1].vertices[7].y = 0.0;
		bodyConf->blocksConf[1].vertices[7].z = 1.0;
	}
	
	if(blocksNum > 2)
	{
		// Third block
		bodyConf->blocksConf[2].name = "thirdBlock";
		bodyConf->blocksConf[2].modelType = "modelThree";
		bodyConf->blocksConf[2].solverType = "customSolver";
		bodyConf->blocksConf[2].meshType = "tetrMesh";
		// Bottom
		bodyConf->blocksConf[2].vertices[0].x = 0.66;
		bodyConf->blocksConf[2].vertices[0].y = 0.0;
		bodyConf->blocksConf[2].vertices[0].z = 0.0;
		bodyConf->blocksConf[2].vertices[1].x = 0.66;
		bodyConf->blocksConf[2].vertices[1].y = 1.0;
		bodyConf->blocksConf[2].vertices[1].z = 0.0;
		bodyConf->blocksConf[2].vertices[2].x = 1.0;
		bodyConf->blocksConf[2].vertices[2].y = 1.0;
		bodyConf->blocksConf[2].vertices[2].z = 0.0;
		bodyConf->blocksConf[2].vertices[3].x = 1.0;
		bodyConf->blocksConf[2].vertices[3].y = 0.0;
		bodyConf->blocksConf[2].vertices[3].z = 0.0;
		// Top
		bodyConf->blocksConf[2].vertices[4].x = 0.66;
		bodyConf->blocksConf[2].vertices[4].y = 0.0;
		bodyConf->blocksConf[2].vertices[4].z = 1.0;
		bodyConf->blocksConf[2].vertices[5].x = 0.66;
		bodyConf->blocksConf[2].vertices[5].y = 1.0;
		bodyConf->blocksConf[2].vertices[5].z = 1.0;
		bodyConf->blocksConf[2].vertices[6].x = 1.0;
		bodyConf->blocksConf[2].vertices[6].y = 1.0;
		bodyConf->blocksConf[2].vertices[6].z = 1.0;
		bodyConf->blocksConf[2].vertices[7].x = 1.0;
		bodyConf->blocksConf[2].vertices[7].y = 0.0;
		bodyConf->blocksConf[2].vertices[7].z = 1.0;
	}

	return Body(bodyConf);
};

void testA() {
	printf("==== Test A ====\n");
	Body b = loadBody("modelOne", "defaultSolver", 1);
	b.load();
	b.doCalc();
	printf("\n");
}

void testB() {
	printf("==== Test B ====\n");
	Body b = loadBody("modelTwo", "customSolver", 2);
	b.load();
	b.doCalc();
	printf("\n");
}

void testC() {
	printf("==== Test C ====\n");
	Body b = loadBody("modelThree", "customSolver", 3);
	b.load();
	b.doCalc();
	printf("\n");
}

void testD() {
	printf("==== Test D ====\n");
	Body b1 = loadBody("modelOne", "defaultSolver", 1);
	b1.load();
	Body b2 = loadBody("modelThree", "customSolver", 1);
	b2.load();
	b1.doCalc();
	b2.doCalc();
	printf("\n");
}

void testE() {
	printf("==== Test E ====\n");
	Body b = loadBody("modelOne", "customSolver", 3);
	b.load();
	b.doCalc();
	printf("\n");
}

void testF() {
	printf("==== Test F ====\n");
	Body b = loadBody("modelTwo", "defaultSolver", 3);
	b.load();
	b.doCalc();
	printf("\n");
}

int main() {
	testA();
	testB();
	testC();
	testD();
	testE();
	testF();
	return 0;
}
