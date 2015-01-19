#include "libgcm/Engine.hpp"
#include "libgcm/Launcher.hpp"

#define BLOCKS_IN_TEST_BODY 3

using namespace gcm;

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
	launcher.loadScene(engine, launcher.taskD);
	
	engine.doNextStep();
}

int main() {	
	testA();
	testB();
	testC();
	testD();
	return 0;
}
