#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <map>
#include <string>
#include <vector>
#include <stdio.h>

#include "Model.hpp"
#include "Solver.hpp"
#include "Body.hpp"

class Engine
{
	protected:
		std::map<std::string, Model*> rheologyModels;
		std::map<std::string, Solver*> numericalMethods;			
		std::vector<Body*> bodies;
		
	public:
		Engine();
		~Engine();
		
		void cleanUp();
		
		void registerRheologyModel(Model* model);
		void registerNumericalMethod(Solver* solver);
		
		Model* getRheologyModel(std::string modelType);
		Solver* getNumericalMethod(std::string solverType);
		
		Body* getBody(unsigned char num);
		void addBody(Body* body);
		
		void doNextStep();
};


#endif	/* ENGINE_HPP */
