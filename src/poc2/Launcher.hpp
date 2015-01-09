#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

#include "Engine.hpp"

struct Task
{
	unsigned char blocksNum;
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
		Task taskD1;
		Task taskD2;
		Task taskE;
		Task taskF;
		std::vector<CalcNode> vertices;
		Launcher();
		
		void loadScene(Engine& engine, Task task);
	
};

#endif /* LAUNCHER_HPP */
