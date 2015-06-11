#include "Engine.hpp"

using namespace gcm;

Engine::Engine() {}

Engine::Engine(const Task &task)
{
	currentTime = 0;
	requiredTime = task.requiredTime;
	tau = task.timeStep;
	for(auto it = task.bodies.begin(); it != task.bodies.end(); it++) {
		Body *body = new Body(*it, this);
		bodies.push_back(body);
	}
	
	registerRheologyModel( new IdealElasticRheologyModel() );
	registerGcmSolver( new IdealElasticGcmSolver() );
}

void Engine::registerRheologyModel(RheologyModel* model)
{
	if(model) {
		rheologyModels[model->getType()] = model;
		printf("Engine: registered rheology model: %s\n", model->getType().c_str());
	}
}

void Engine::registerGcmSolver(GcmSolver* solver)
{
	if(solver) {
		GcmSolvers[solver->getType()] = solver;
		printf("Engine: registered numerical method: %s\n", solver->getType().c_str());
	}
}

RheologyModel *Engine::getRheologyModel(std::string type) const {
	return rheologyModels.at(type);
}

GcmSolver *Engine::getSolver(std::string type) const {
	return GcmSolvers.at(type);
}

void Engine::calculate() {
	while(currentTime < requiredTime)
		doNextTimeStep();
}

void Engine::doNextTimeStep() {
	for( auto it = bodies.begin(); it != bodies.end(); ++it )
		(*it)->doNextTimeStep();
}

real Engine::getCurrentTime() const {
	return currentTime;
}