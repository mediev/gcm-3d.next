#include "Launcher.hpp"

using namespace gcm;

Launcher::Launcher() {
	Geometry geom;
	geom.x0 = geom.y0 = geom.z0 = 0;
	geom.hx = geom.hy = geom.hz = 1;
	
	BlockProperties blProp;
	blProp.computationalCost = 1;
	blProp.geometry = geom;
	blProp.meshType = "CubicMesh";
	blProp.modelType = "IdealElasticRheologyModel";
	blProp.solverType = "IdealElasticGcmSolver";
	blProp.spatialStep = 0.1;
	
	BodyProperties boProp;
	boProp.computationalCost = 1;
	boProp.blocks.push_back(blProp);
	
	task.bodies.push_back(boProp);
	task.timeStep = 0.1 / 1e+4;
	task.requiredTime = task.timeStep;
	
}