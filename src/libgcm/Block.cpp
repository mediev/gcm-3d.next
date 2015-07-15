#include "Block.hpp"

using namespace gcm;

Block::Block() {
}

void Block::loadTask(const BlockProperties& blProp) {
	printf("Loading task in block %d\n", id);
	Engine& engine = Engine::getInstance();
	model = engine.getRheologyModel(blProp.modelType);
	solver = engine.getSolver(blProp.solverType);
	
	std::map<int, real> procLoad;
	Dispatcher::getInstance().getProportionsOfBlockDivision(id, procLoad);
	
	if (blProp.meshType == "CubicMesh") {
		CubicMeshLoader &loader = CubicMeshLoader::getInstance();
		CubicMesh *coarseMesh = new CubicMesh();
		coarseMesh->setId(-1);
		coarseMesh->setRheologyModel(model);
		loader.loadCoarseMesh(coarseMesh, blProp.geometry, blProp.coarseSpatialStep);

		InertiaMomentPartitioner part;
		part.partMesh(this, coarseMesh, procLoad);
		for(uint i = 0; i < meshes.size(); i++) {
			meshes[i]->setId(1000 * id + i);
			CubicMesh *fineMesh = new CubicMesh();
			fineMesh->setRheologyModel(model);
			if( meshes[i]->getRank() == MPI::COMM_WORLD.Get_rank() ) {
				loader.loadFineMeshFromCoarse(static_cast<CubicMesh *> (meshes[i]),
				                              fineMesh, blProp.spatialStep);
				meshes[i] = fineMesh;
			}
		}

	} else if (blProp.meshType == "TetrahedronMesh") {
		TetrMeshFirstOrder* coarseMesh = new TetrMeshFirstOrder();
		coarseMesh->setId(-2);
		coarseMesh->setRheologyModel(model);

		TetrahedronMeshLoader::getInstance().loadMesh(coarseMesh, "models/cube.geo", blProp.spatialStep);

		InertiaMomentPartitioner part;
		part.partMesh(this, coarseMesh, procLoad);
		for(uint i = 0; i < meshes.size(); i++) {
			meshes[i]->initValuesInNodes();
			meshes[i]->preProcess();
			meshes[i]->setId(1000 * id + i);
		}
	}
}

void Block::addMesh(Mesh* mesh) {
	meshes.push_back(mesh);
}

void Block::doNextTimeStep() {
	for(auto mesh = meshes.begin(); mesh != meshes.end(); mesh++)
		if( (*mesh)->getRank() == MPI::COMM_WORLD.Get_rank() ) {
			solver->doNextTimeStep(*mesh);
			(*mesh)->snapshot(1);
		}
}

void Block::checkTopology(real tau)
{
	for(auto mesh = meshes.begin(); mesh != meshes.end(); mesh++)
		(*mesh)->checkTopology(tau);
}

void Block::setId(uint _id) {
	id = _id;
}

uint Block::getId() {
	return id;
}
