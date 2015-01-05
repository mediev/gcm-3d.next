#include <stdio.h>
#include <string>

#include "Mesh.hpp"
#include "Model.hpp"
#include "Solver.hpp"

class Body {
protected:
	Mesh* mesh;
	Solver* solver;
	Model* model;
public:
	Body(Mesh* mesh, Solver* solver, Model* model) : 
		mesh(mesh), solver(solver), model(model) {};
	void doCalc()
	{
		unsigned int size = mesh->getNodesNumber();
		for(int i = 0; i < size; i++)
			solver->doCalc(mesh->getNode(i));
	}
};

Body loadBody(std::string modelType, std::string solverType, std::string meshType) {
	Solver* solver;
	Model* model;
	Mesh* mesh;

	if (solverType == "defaultSolver") {
		solver = new DefaultSolver();
	} else if (solverType == "customSolver") {
		solver = new CustomSolver();
	}

	if (modelType == "modelOne") {
		model = new ModelOne();
	} else if (modelType == "modelTwo") {
		model = new ModelTwo();
	} else if (modelType == "modelThree") {
		model = new ModelThree();
	}

	if (meshType == "tetrMesh") {
		mesh = new TetrMesh();
	} else if (meshType == "cubicMesh") {
		mesh = new CubicMesh();
	}

	mesh->setModel(model);
	mesh->load();

	return Body(mesh, solver, model);
};

void testA() {
	printf("==== Test A ====\n");
	Body b = loadBody("modelOne", "defaultSolver", "tetrMesh");
	b.doCalc();
	printf("\n");
}

void testB() {
	printf("==== Test B ====\n");
	Body b = loadBody("modelTwo", "customSolver", "cubicMesh");
	b.doCalc();
	printf("\n");
}

void testC() {
	printf("==== Test C ====\n");
	Body b = loadBody("modelThree", "customSolver", "tetrMesh");
	b.doCalc();
	printf("\n");
}

void testD() {
	printf("==== Test D ====\n");
	Body b1 = loadBody("modelOne", "defaultSolver", "cubicMesh");
	Body b2 = loadBody("modelThree", "customSolver", "tetrMesh");
	b1.doCalc();
	b2.doCalc();
	printf("\n");
}

void testE() {
	printf("==== Test E ====\n");
	Body b = loadBody("modelOne", "customSolver", "tetrMesh");
	b.doCalc();
	printf("\n");
}

void testF() {
	printf("==== Test F ====\n");
	Body b = loadBody("modelTwo", "defaultSolver", "tetrMesh");
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