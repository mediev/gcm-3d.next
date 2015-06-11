#include "libgcm/Engine.hpp"
#include "libgcm/Launcher.hpp"


using namespace gcm;

int main() {
	Launcher launcher;
	Engine *engine = new Engine(launcher.task);
	
	engine->calculate();

	return 0;
}
