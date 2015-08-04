#include "Launcher.hpp"

using namespace gcm;

Launcher::Launcher() {
}

Launcher::Launcher(const uint taskNum)
{
	if (taskNum == 222) {
		Geometry geom;
		geom.x0 = geom.y0 = -5; geom.z0 = 7;
		geom.hx = 10;
		geom.hy = 10;
		geom.hz = 20;
		BlockProperties blProp1;
		blProp1.computationalCost = 2;
		blProp1.geometry = geom;
		blProp1.meshType = "CubicMesh";
		blProp1.spatialStep = 0.25;
		blProp1.modelType = "IdealPlasticRheologyModel";
		blProp1.solverType = "FirstOrderSolver";
		blProp1.coarseSpatialStep = 1;
		blProp1.id = 00;

		geom.x0 = geom.y0 = -5; geom.z0 = 27;
		geom.hx = 10;
		geom.hy = 10;
		geom.hz = 10;
		BlockProperties blProp2;
		blProp2.computationalCost = 1;
		blProp2.geometry = geom;
		blProp2.meshType = "CubicMesh";
		blProp2.spatialStep = 0.25;
		blProp2.modelType = "IdealElasticRheologyModel";
		blProp2.solverType = "FirstOrderSolver";
		blProp2.coarseSpatialStep = 1;
		blProp2.id = 01;

		BodyProperties boProp1;
		boProp1.computationalCost = 3;
		boProp1.blocks.push_back(blProp1);
		boProp1.blocks.push_back(blProp2);
		boProp1.id = 0;

		task.bodies.push_back(boProp1);

		BlockProperties blProp3;
		blProp3.computationalCost = 1;
		blProp3.modelType = "IdealElasticRheologyModel";
		blProp3.solverType = "FirstOrderSolver";
		blProp3.meshType = "TetrahedronMesh_IMP";
		blProp3.spatialStep = 1.0;
		blProp3.id = 10;

		BodyProperties boProp2;
		boProp2.computationalCost = 1;
		boProp2.blocks.push_back(blProp3);
		boProp2.id = 1;

		task.bodies.push_back(boProp2);

		task.timeStep = 0.1 / 1e+4;
		task.requiredTime = task.timeStep;

	} else {
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
			blProp.coarseSpatialStep = 0.2;
			blProp.spatialStep = 0.1;
		} else if(taskNum == 2) {
			blProp.meshType = "TetrahedronMesh";
			blProp.coarseSpatialStep = 2.0;
			blProp.spatialStep = 1.0;
		} else if(taskNum == 21) {
			blProp.meshType = "CubicMesh_Metis";
			blProp.coarseSpatialStep = 0.2;
			blProp.spatialStep = 0.1;
		}

		blProp.modelType = "IdealPlasticRheologyModel";
		blProp.solverType = "FirstOrderSolver";
		blProp.id = 00;

		BodyProperties boProp;
		boProp.computationalCost = 1;
		boProp.blocks.push_back(blProp);
		boProp.id = 0;

		task.bodies.push_back(boProp);
		task.timeStep = 0.1 / 1e+4;
		task.requiredTime = 2*task.timeStep;
	}
}
