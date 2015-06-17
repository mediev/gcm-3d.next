#include "libgcm/Engine.hpp"
#include "libgcm/Launcher.hpp"


using namespace gcm;

int main() {
	MPI::Init();
	Launcher launcher;
	Engine& engine = Engine::getInstance();
	engine.loadTask(launcher.task);
	
	engine.calculate();
	MPI::Finalize();
	return 0;
}
