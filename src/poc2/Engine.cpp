#include "Engine.hpp"

Engine::Engine()
{
	registerRheologyModel( new ModelOne() );
	registerRheologyModel( new ModelTwo() );
	registerRheologyModel( new ModelThree() );
	
	registerNumericalMethod( new DefaultSolver() );
	registerNumericalMethod( new CustomSolver() );
}

Engine::~Engine()
{
    cleanUp();
}

void Engine::cleanUp()
{
	for(auto& b: bodies)
        delete b;
    bodies.clear();
    printf("Engine: cleaned!\n");
}

void Engine::registerRheologyModel(Model* model)
{
	if(model) {
		rheologyModels[model->getType()] = model;
		printf("Engine: registered rheology model: %s\n", model->getType().c_str());
	}
}

void Engine::registerNumericalMethod(Solver* solver)
{
	if(solver) {
		numericalMethods[solver->getType()] = solver;
		printf("Engine: registered numerical method: %s\n", solver->getType().c_str());
	}
}

Body* Engine::getBody(unsigned char num)
{
    //assert_lt(num, bodies.size() );
    return bodies[num];
}

void Engine::addBody(Body* body)
{
    bodies.push_back(body);
}

void Engine::doNextStep()
{
	for( std::vector<Body*>::iterator it = bodies.begin(); it != bodies.end(); ++it )
		(*it)->doCalc();
}
