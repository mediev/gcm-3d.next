#include <cstdlib>

#include <gmsh/Gmsh.h>

#include "libgcm/Engine.hpp"
#include "libgcm/Launcher.hpp"
#include "libgcm/util/Types.hpp"

using namespace gcm;

int main(int argc, char* argv[]) {

	if(argc < 2) {
			fprintf(stderr, "Usage: ./gcm [task number]\n");
			return -1;
	}
	const uint taskNum = atoi(argv[1]);

	MPI::Init();
	GmshInitialize();
	Launcher launcher(taskNum);

	Engine& engine = Engine::getInstance();
	engine.loadTask(launcher.task);
	
	engine.calculate();
	GmshFinalize();
	MPI::Finalize();

	return 0;
}
