#include "Engine.hpp"

using namespace gcm;

const std::string Engine::SNAPSHOT_OUTPUT_PATH_PATTERN = "snap_mesh_%{MESH}%{SUFFIX}_cpu_%{RANK}_step_%{STEP}.%{EXT}";

Engine::Engine()
{
	rank = MPI::COMM_WORLD.Get_rank();
	numberOfWorkers = MPI::COMM_WORLD.Get_size();
	registerRheologyModel( new IdealElasticRheologyModel() );
	registerRheologyModel( new IdealPlasticRheologyModel() );
	registerGcmSolver( new FirstOrderSolver() );
	
	dataBus = new DataBus();

	fixedTimeStep = std::numeric_limits<real>::infinity();
}

void Engine::loadTask(const Task &task)
{
	currentTime = 0;
	requiredTime = task.requiredTime;
	fixedTimeStep = task.timeStep;
	for(uint i = 0; i < task.bodies.size(); i++) {
		Body *body = new Body();
		body->setId(task.bodies[i].id);
		bodies.push_back(body);
	}
	Dispatcher::getInstance().distributeProcessors(task, numberOfWorkers);
	for(uint i = 0; i < task.bodies.size(); i++)
		bodies[i]->loadTask(task.bodies[i]);
	
}

void Engine::setTimeStep(real dt)
{
	if( (dt > 0) && (dt < fixedTimeStep) )
		fixedTimeStep = dt;
}

real Engine::getTimeStep()
{
	return fixedTimeStep;
}

void Engine::registerRheologyModel(RheologyModel* model)
{
	if(model) {
		rheologyModels[model->getType()] = model;
		printf("Engine: registered rheology model: %s\n", model->getType().c_str());
	}
}

void Engine::registerGcmSolver(Solver* solver)
{
	if(solver) {
		gcmSolvers[solver->getType()] = solver;
		printf("Engine: registered numerical method: %s\n", solver->getType().c_str());
	}
}

RheologyModel *Engine::getRheologyModel(std::string type) const {
	return rheologyModels.at(type);
}

Solver *Engine::getSolver(std::string type) const {
	return gcmSolvers.at(type);
}

void Engine::calculate() {
	while(currentTime < requiredTime) {
		
		doNextTimeStep();
		currentTime += fixedTimeStep;
	}
}

void Engine::doNextTimeStep() {
	printf("Engine: starting next step: time = %f\n", getCurrentTime());
	MPI::COMM_WORLD.Barrier();
	for( auto it = bodies.begin(); it != bodies.end(); ++it )
		(*it)->doNextTimeStep();
	MPI::COMM_WORLD.Barrier();
	for( auto it = bodies.begin(); it != bodies.end(); ++it )
		(*it)->replaceNewAndCurrentNodes();
}

real Engine::getCurrentTime() const {
	return currentTime;
}

Engine::~Engine()
{
    clear();
}

void Engine::clear() {
    // clear memory
    for(auto& b: bodies)
        delete b;
    bodies.clear();
    rheologyModels.clear();
    gcmSolvers.clear();

    delete dataBus;

    // clear state
    currentTime = 0;
    fixedTimeStep = -1;
}

uint Engine::getRank()
{
	return rank;
}

uint Engine::getNumberOfWorkers() {
	return numberOfWorkers;
}

DataBus* Engine::getDataBus()
{
	return dataBus;
}
