#include "Launcher.hpp"

using namespace gcm;

Launcher::Launcher() {
}

Launcher::Launcher(const uint taskNum)
{
	Geometry geom;
	geom.x0 = geom.y0 = geom.z0 = 0;

	geom.hx = 2;
	geom.hy = 1;
	geom.hz = 1;
	
	BlockProperties blProp;
	blProp.computationalCost = 1;
	blProp.geometry = geom;

	if(taskNum == 1) {
		blProp.meshType = "CubicMesh";
		blProp.spatialStep = 0.1;
	} else if(taskNum == 2) {
		blProp.meshType = "TetrahedronMesh";
		blProp.spatialStep = 1.0;
	}

	blProp.modelType = "IdealElasticRheologyModel";
	blProp.solverType = "IdealElasticGcmSolver";
	blProp.spatialStep = 0.1;
	blProp.coarseSpatialStep = 0.2;

	BodyProperties boProp;
	boProp.computationalCost = 1;
	boProp.blocks.push_back(blProp);

	task.bodies.push_back(boProp);
	task.timeStep = 0.1 / 1e+4;
	task.requiredTime = task.timeStep;
}
