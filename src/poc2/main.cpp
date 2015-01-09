#include "Body.hpp"
#include "Block.hpp"
#include "Mesh.hpp"
#include "Model.hpp"
#include "Solver.hpp"
#include "Engine.hpp"
#include "Launcher.hpp"

#define BLOCKS_IN_TEST_BODY 3

void testA() {
	printf("\n==== Test A ====\n");
	Engine engine;
	Launcher launcher;
	launcher.loadScene(engine, launcher.taskA);
	
	engine.doNextStep();
}

void testB() {
	printf("\n==== Test B ====\n");
	Engine engine;
	Launcher launcher;
	launcher.loadScene(engine, launcher.taskB);
	
	engine.doNextStep();
}

void testC() {
	printf("\n==== Test C ====\n");
	Engine engine;
	Launcher launcher;
	launcher.loadScene(engine, launcher.taskC);
	
	engine.doNextStep();
}

void testD() {
	printf("\n==== Test D ====\n");
	Engine engine;
	Launcher launcher;
	launcher.loadScene(engine, launcher.taskD1);
	launcher.loadScene(engine, launcher.taskD2);
	
	engine.doNextStep();
}

void testE() {
	printf("\n==== Test E ====\n");
	Engine engine;
	Launcher launcher;
	launcher.loadScene(engine, launcher.taskE);
	
	engine.doNextStep();
}

void testF() {
	printf("\n==== Test F ====\n");
	Engine engine;
	Launcher launcher;
	launcher.loadScene(engine, launcher.taskF);
	
	engine.doNextStep();
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
