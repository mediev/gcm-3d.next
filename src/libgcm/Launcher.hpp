#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

#include "libgcm/Engine.hpp"


namespace gcm {
	struct Task
	{
		unsigned char numOfBlocks;
		std::string modelType;
		std::string solverType;
		std::string meshType;
	};

	class Launcher
	{
		public:
			Task taskA;
			Task taskB;
			Task taskC;
			Task taskD;
			std::vector<CalcNode> vertices;
			Launcher();

			void loadScene(Engine& engine, Task task);

	};
}
#endif /* LAUNCHER_HPP */
