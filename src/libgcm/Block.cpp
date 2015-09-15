#include "Block.hpp"

using namespace gcm;
using namespace MPI;

using std::string;
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
	
	uint nparts = engine.getNumberOfWorkers();
	DataBus* dataBus = engine.getDataBus();

	if (blProp.meshType == "CubicMesh") {
		CubicMeshLoader &loader = CubicMeshLoader::getInstance();
		CubicMesh *coarseMesh = new CubicMesh();
		coarseMesh->setId(-1);
		coarseMesh->setRheologyModel(model);
		loader.loadCoarseMesh(coarseMesh, blProp.geometry, blProp.coarseSpatialStep);

		InertiaMomentPartitioner part;
		part.partMesh(this, coarseMesh, procLoad);
		for(uint i = 0; i < meshes.size(); i++)
			if (meshes[i]->getRank() == MPI::COMM_WORLD.Get_rank()) {
				meshes[i]->setId(1000 * id + i);
				CubicMesh *fineMesh = new CubicMesh();
				fineMesh->setRheologyModel(model);
				loader.loadFineMeshFromCoarse(static_cast<CubicMesh *> (meshes[i]),
				                              fineMesh, blProp.spatialStep);
				meshes[i] = fineMesh;
				int sizeOfValuesInPDE = model->getSizeOfValuesInPDE();
				real* valuesInPDE = new real[sizeOfValuesInPDE];
				for(int j = 0; j < sizeOfValuesInPDE; j++)
					valuesInPDE[j] = 0;
				valuesInPDE[3] = -1;
				AABB area = AABB(0.1, 0.3, -10, 10, -10, 10);
				meshes[i]->setInitialState(valuesInPDE, area);
				MaterialPtr material = makeMaterialPtr("testMaterial", 1, 1, 1);
				area.maxX = 10; area.minX = -10;
				meshes[i]->setMaterial(material, area);
				delete [] valuesInPDE;
			}
	} else if (blProp.meshType == "TetrahedronMesh_IMP") {
		TetrMeshFirstOrder* coarseMesh = new TetrMeshFirstOrder();
		coarseMesh->setId(-2);
		coarseMesh->setRheologyModel(model);
		TetrMeshLoader::getInstance().loadMesh(coarseMesh, "models/cube.geo", blProp.spatialStep);

		InertiaMomentPartitioner part;
		part.partMesh(this, coarseMesh, procLoad);
		for(uint i = 0; i < meshes.size(); i++) {
			meshes[i]->initValuesInNodes();
			meshes[i]->preProcess();
			meshes[i]->setId(1000 * id + i);
		}
	} else if (blProp.meshType == "TetrahedronMesh") {
		if (engine.getRank() == 0) {
			// Creating coarse mesh
			TetrMeshFirstOrder* coarseMesh = new TetrMeshFirstOrder();
			coarseMesh->setId(999);
			coarseMesh->setRheologyModel(model);
			TetrMeshLoader::getInstance().loadMesh(coarseMesh, "models/cube.geo", blProp.coarseSpatialStep);

			// Partitioning
			TetrMeshFirstOrder* coarsePart = new TetrMeshFirstOrder [nparts];
			MetisPartitioner::getInstance().partMesh(coarseMesh, nparts, coarsePart);

			coarsePart[0].setId(engine.getRank() * 100);
			coarsePart[0].snapshot(0);

			// Distributing
			dataBus->transferMesh(coarsePart);
			coarsePart[0].preProcess();

			// Writing *.geo file for part
			string geoName = "models/parts/part_" + to_string(engine.getRank()) + ".geo";
			Mesh2GeoLoader geoLoader;
			geoLoader.writeGeoFile(geoName, &coarsePart[0]);

			// Refinement
			TetrMeshFirstOrder* fineMesh = new TetrMeshFirstOrder();
			fineMesh->setRheologyModel(model);
			fineMesh->setId(engine.getRank() * 100 + 1);
			TetrMeshLoader::getInstance().loadMesh(fineMesh, geoName, blProp.spatialStep);
			fineMesh->snapshot(0);

			this->addMesh(fineMesh);

		} else {
			// Distributing
			TetrMeshFirstOrder* coarsePart = new TetrMeshFirstOrder();
			dataBus->transferMesh(coarsePart);
			coarsePart->preProcess();

			coarsePart->setId(engine.getRank() * 100);
			coarsePart->snapshot(0);

			// Writing *.geo file for part
			string geoName = "models/parts/part_" + to_string(engine.getRank()) + ".geo";
			Mesh2GeoLoader geoLoader;
			geoLoader.writeGeoFile(geoName, coarsePart);

			// Refinement
			TetrMeshFirstOrder* fineMesh = new TetrMeshFirstOrder();
			fineMesh->setRheologyModel(model);
			fineMesh->setId(engine.getRank() * 100 + 1);
			TetrMeshLoader::getInstance().loadMesh(fineMesh, geoName, blProp.spatialStep);
			fineMesh->snapshot(0);

			this->addMesh(fineMesh);
		}
	} else if (blProp.meshType == "CubicMesh_Metis") {
		if (engine.getRank() == 0) {
			// Creating coarse mesh
			CubicMesh* coarseMesh = new CubicMesh();
			coarseMesh->setId(999);
			coarseMesh->setRheologyModel(model);
			CubicMeshLoader::getInstance().loadCoarseMesh(coarseMesh, blProp.geometry, blProp.coarseSpatialStep);

			// Partitioning
			CubicMesh* coarsePart = new CubicMesh [nparts];
			MetisPartitioner::getInstance().partMesh(coarseMesh, nparts, coarsePart);

			coarsePart[0].setId(engine.getRank() * 100);
			coarsePart[0].snapshot(0);

			// Distributing
			dataBus->transferMesh(coarsePart);
			coarsePart[0].preProcess();

			// Refinement
			CubicMesh* fineMesh = new CubicMesh();
			fineMesh->setRheologyModel(model);
			fineMesh->setId(engine.getRank() * 100 + 1);
			CubicMeshLoader::getInstance().loadFineMeshFromCoarse(&coarsePart[0], fineMesh, blProp.spatialStep);
			fineMesh->snapshot(0);

			this->addMesh(fineMesh);
		} else {
			// Distributing
			CubicMesh* coarsePart = new CubicMesh();
			dataBus->transferMesh(coarsePart);
			coarsePart->preProcess();

			coarsePart->setId(engine.getRank() * 100);
			coarsePart->snapshot(0);

			// Refinement
			CubicMesh* fineMesh = new cubicMesh();
			fineMesh->setRheologyModel(model);
			fineMesh->setId(engine.getRank() * 100 + 1);
			CubicMeshLoader::getInstance().loadMesh(coarsePart, fineMesh, blProp.spatialStep);
			fineMesh->snapshot(0);

			this->addMesh(fineMesh);
		}
	}
}

void Block::addMesh(Mesh* mesh) {
	meshes.push_back(mesh);
}

void Block::doNextTimeStep() {
	Engine &engine = Engine::getInstance();
	for(auto mesh = meshes.begin(); mesh != meshes.end(); mesh++)
		if( (*mesh)->getRank() == COMM_WORLD.Get_rank() ) {
			solver->doNextTimeStep(*mesh);
			(*mesh)->snapshot((int) (engine.getCurrentTime()/engine.getTimeStep()));
		}
}

void Block::replaceNewAndCurrentNodes() {
	for(auto mesh = meshes.begin(); mesh != meshes.end(); mesh++)
		if( (*mesh)->getRank() == MPI::COMM_WORLD.Get_rank() )
			(*mesh)->replaceNewAndCurrentNodes();
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
