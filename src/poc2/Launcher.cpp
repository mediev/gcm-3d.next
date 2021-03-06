#include "Launcher.hpp"

Launcher::Launcher()
{
	// Types of entities in 1'st block in every test
	taskA.blocksNum = 1;
	taskA.modelType = "modelOne";
	taskA.solverType = "defaultSolver";
	taskA.meshType = "tetrMesh";
	
	taskB.blocksNum = 2;
	taskB.modelType = "modelTwo";
	taskB.solverType = "customSolver";
	taskB.meshType = "cubicMesh";
	
	taskC.blocksNum = 3;
	taskC.modelType = "modelThree";
	taskC.solverType = "customSolver";
	taskC.meshType = "tetrMesh";
	
	taskD1.blocksNum = 1;
	taskD1.modelType = "modelOne";
	taskD1.solverType = "defaultSolver";
	taskD1.meshType = "tetrMesh";
	
	taskD2.blocksNum = 1;
	taskD2.modelType = "modelThree";
	taskD2.solverType = "customSolver";
	taskD2.meshType = "cubicMesh";

	taskE.blocksNum = 3;
	taskE.modelType = "modelOne";
	taskE.solverType = "customSolver";
	taskE.meshType = "cubicMesh";
	
	taskF.blocksNum = 3;
	taskF.modelType = "modelTwo";
	taskF.solverType = "defaultSolver";
	taskF.meshType = "tetrMesh";
	
	for(unsigned char i = 0; i < 24; i++)
		vertices.push_back(CalcNode(0, 0, 0));
	
	// First block
	// Bottom
	vertices[0].coords[0] = 0.0;
	vertices[0].coords[1] = 0.0;
	vertices[0].coords[2] = 0.0;
	vertices[1].coords[0] = 0.0;
	vertices[1].coords[1] = 1.0;
	vertices[1].coords[2] = 0.0;
	vertices[2].coords[0] = 0.33;
	vertices[2].coords[1] = 1.0;
	vertices[2].coords[2] = 0.0;
	vertices[3].coords[0] = 0.33;
	vertices[3].coords[1] = 0.0;
	vertices[3].coords[2] = 0.0;
	// Top
	vertices[4].coords[0] = 0.0;
	vertices[4].coords[1] = 0.0;
	vertices[4].coords[2] = 1.0;
	vertices[5].coords[0] = 0.0;
	vertices[5].coords[1] = 1.0;
	vertices[5].coords[2] = 1.0;
	vertices[6].coords[0] = 0.33;
	vertices[6].coords[1] = 1.0;
	vertices[6].coords[2] = 1.0;
	vertices[7].coords[0] = 0.33;
	vertices[7].coords[1] = 0.0;
	vertices[7].coords[2] = 1.0;

	// Second block
	// Bottom
	vertices[8].coords[0] = 0.33;
	vertices[8].coords[1] = 0.0;
	vertices[8].coords[2] = 0.0;
	vertices[9].coords[0] = 0.33;
	vertices[9].coords[1] = 1.0;
	vertices[9].coords[2] = 0.0;
	vertices[10].coords[0] = 0.66;
	vertices[10].coords[1] = 1.0;
	vertices[10].coords[2] = 0.0;
	vertices[11].coords[0] = 0.66;
	vertices[11].coords[1] = 0.0;
	vertices[11].coords[2] = 0.0;
	// Top
	vertices[12].coords[0] = 0.33;
	vertices[12].coords[1] = 0.0;
	vertices[12].coords[2] = 1.0;
	vertices[13].coords[0] = 0.33;
	vertices[13].coords[1] = 1.0;
	vertices[13].coords[2] = 1.0;
	vertices[14].coords[0] = 0.66;
	vertices[14].coords[1] = 1.0;
	vertices[14].coords[2] = 1.0;
	vertices[15].coords[0] = 0.66;
	vertices[15].coords[1] = 0.0;
	vertices[15].coords[2] = 1.0;

	// Third block
	// Bottom
	vertices[16].coords[0] = 0.66;
	vertices[16].coords[1] = 0.0;
	vertices[16].coords[2] = 0.0;
	vertices[17].coords[0] = 0.66;
	vertices[17].coords[1] = 1.0;
	vertices[17].coords[2] = 0.0;
	vertices[18].coords[0] = 1.0;
	vertices[18].coords[1] = 1.0;
	vertices[18].coords[2] = 0.0;
	vertices[19].coords[0] = 1.0;
	vertices[19].coords[1] = 0.0;
	vertices[19].coords[2] = 0.0;
	// Top
	vertices[20].coords[0] = 0.66;
	vertices[20].coords[1] = 0.0;
	vertices[20].coords[2] = 1.0;
	vertices[21].coords[0] = 0.66;
	vertices[21].coords[1] = 1.0;
	vertices[21].coords[2] = 1.0;
	vertices[22].coords[0] = 1.0;
	vertices[22].coords[1] = 1.0;
	vertices[22].coords[2] = 1.0;
	vertices[23].coords[0] = 1.0;
	vertices[23].coords[1] = 0.0;
	vertices[23].coords[2] = 1.0;

}

void Launcher::loadScene(Engine& engine, Task task)
{
	Body* body = new Body();
	
	for(int i = 0; i < task.blocksNum; i++)
	{
		Model* model;
		Solver* solver;
		Mesh* mesh;
		std::string name;
		
		if(i == 0) {
			name = "firstBlock";
			if (task.modelType == "modelOne") {
				model = new ModelOne();
			} else if (task.modelType == "modelTwo") {
				model = new ModelTwo();
			} else if (task.modelType == "modelThree") {
				model = new ModelThree();
			}
			
			if (task.solverType == "defaultSolver") {
				solver = new DefaultSolver();
			} else if (task.solverType == "customSolver") {
				solver = new CustomSolver();
			}
			
			if (task.meshType == "tetrMesh") {
				mesh = new TetrMesh();
			} else if (task.meshType == "cubicMesh") {
				mesh = new CubicMesh();
			}
		} else if(i == 1) {
			name = "secondBlock";
			model = new ModelOne();
			solver = new DefaultSolver();
			mesh = new TetrMesh();
		} else if(i == 2) {
			name = "thirdBlock";
			model = new ModelThree();
			solver = new CustomSolver();
			mesh = new CubicMesh();
		}
		
		body->addBlock(Block(name, model, solver, mesh));
		body->setModel(i);
	}
	
	body->load(vertices);
	engine.addBody(body);
}
