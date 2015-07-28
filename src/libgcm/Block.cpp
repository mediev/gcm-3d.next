#include "Block.hpp"

using namespace gcm;
using namespace MPI;

using std::to_string;

Block::Block()
{
}

void Block::loadTask(const BlockProperties& blProp) {
	Engine& engine = Engine::getInstance();
	printf("Proc #%d: Loading task in block %d\n", engine.getRank(), id);

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
			if( meshes[i]->getRank() == COMM_WORLD.Get_rank() ) {
				loader.loadFineMeshFromCoarse(static_cast<CubicMesh *> (meshes[i]),
				                              fineMesh, blProp.spatialStep);
				meshes[i] = fineMesh;
			}
		}
	} else if (blProp.meshType == "TetrahedronMesh_IMP") {
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
	} else if (blProp.meshType == "TetrahedronMesh") {
		if (engine.getRank() == 0) {
			uint nparts = engine.getNumberOfWorkers();
			TetrMeshFirstOrder* coarseMesh = new TetrMeshFirstOrder();
			coarseMesh->setId(100);
			coarseMesh->setRheologyModel(model);
			TetrahedronMeshLoader::getInstance().loadMesh(coarseMesh, "models/cube.geo", blProp.spatialStep);

			TetrMeshFirstOrder* coarsePart = new TetrMeshFirstOrder [nparts];
			MetisPartitioner::getInstance().partMesh(coarseMesh, nparts, coarsePart);

			DataBus* dataBus = engine.getDataBus();
			for(uint i = 1; i < nparts; i++)
				dataBus->transferMesh(&coarsePart[i], i);

			coarsePart[0].snapshot(0);

		} else {
			TetrMeshFirstOrder* coarsePart = new TetrMeshFirstOrder();

			DataBus* dataBus = engine.getDataBus();
			dataBus->transferMesh(coarsePart, 0);
			coarsePart->snapshot(0);
		}
	} else if (blProp.meshType == "CubicMesh_Metis") {
		if (engine.getRank() == 0) {
			uint nparts = engine.getNumberOfWorkers();
			CubicMesh* coarseMesh = new CubicMesh();
			coarseMesh->setId(200);
			coarseMesh->setRheologyModel(model);

			CubicMeshLoader& loader = CubicMeshLoader::getInstance();
			loader.loadCoarseMesh(coarseMesh, blProp.geometry, blProp.coarseSpatialStep);

			CubicMesh* coarsePart = new CubicMesh [nparts];
			MetisPartitioner::getInstance().partMesh(coarseMesh, nparts, coarsePart);
			for(uint i = 0; i < nparts; i++) {
				CubicMesh* fineMesh = new CubicMesh();
				fineMesh->setId(2000 + i);
				fineMesh->setRheologyModel(model);
				loader.loadFineMeshFromCoarse(&coarsePart[i], fineMesh, blProp.spatialStep);

				this->addMesh(fineMesh);
			}
		} else {

		}
	}
}

void Block::addMesh(Mesh* mesh) {
	meshes.push_back(mesh);
}

void Block::doNextTimeStep() {
	for(auto mesh = meshes.begin(); mesh != meshes.end(); mesh++)
		if( (*mesh)->getRank() == COMM_WORLD.Get_rank() ) {
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
