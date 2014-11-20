#include <stdio.h>
#include <string>

#include "models.hpp"
#include "nodes.hpp"
#include "solvers.hpp"
#include "mesh.hpp"

template <class NodeType> class Body
{
protected:
	Mesh<NodeType>* mesh;
	Solver* solver;
	Model* model;
public:
	Body(Mesh<NodeType>* _mesh, Solver* _solver, Model* _model) : mesh(_mesh), solver(_solver), model(_model)
	{
	}
	void doCalc()
	{
		solver->doCalc(mesh->getNode(0));
	}
};

template <class NodeType> Body<NodeType> loadBody(std::string modelType, std::string solverType, std::string meshType)
{
	Solver* solver;
	Model* model;

	// Ugly (!) - we can *NOT* have just Mesh pointer anymore - it *MUST* be templated
	// It actually means again templating lots of methods in classes around it
	Mesh<NodeType>* mesh;

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

	// Ugly (!) - modelType and meshType can *NOT* be processed separately, since we need *BOTH* node type and mesh type here
	// Current workaround - templated loadTask(),
	//	 but it means that calling function (testX in this case) 
	//	 actually processes model info separately (when decides which loadTask() to call)
	if (meshType == "tetrMesh") {
		mesh = new TetrMesh<NodeType>();
		mesh->load();
	} else if (meshType == "cubicMesh") {
		mesh = new CubicMesh<NodeType>();
		mesh->load();
	}

	return Body<NodeType>(mesh, solver, model);
};

void testA()
{
	printf("==== Test A ====\n");
	Body<CalcNode> b = loadBody<CalcNode>("modelOne", "defaultSolver", "tetrMesh");
	b.doCalc();
	printf("\n");
}

void testB()
{
	printf("==== Test B ====\n");
	Body<CalcNode> b = loadBody<CalcNode>("modelTwo", "defaultSolver", "cubicMesh");
	b.doCalc();
	printf("\n");
}

void testC()
{
	printf("==== Test C ====\n");
	Body<MyNewCalcNode> b = loadBody<MyNewCalcNode>("modelThree", "customSolver", "tetrMesh");
	b.doCalc();
	printf("\n");
}

void testD()
{
	printf("==== Test D ====\n");
	Body<CalcNode> b1 = loadBody<CalcNode>("modelOne", "defaultSolver", "cubicMesh");
	Body<MyNewCalcNode> b2 = loadBody<MyNewCalcNode>("modelThree", "customSolver", "tetrMesh");
	b1.doCalc();
	b2.doCalc();
	printf("\n");
}

int main()
{
	testA();
	testB();
	testC();
	testD();
	return 0;
}
