#include "Block.hpp"

using namespace gcm;

using std::to_string;

Block::Block() {
}

void Block::loadTask(const BlockProperties& prop) {
	Engine& engine = Engine::getInstance();
	model = engine.getRheologyModel(prop.modelType);
	solver = engine.getSolver(prop.solverType);

	if (prop.meshType == "CubicMesh") {
		CubicMeshLoader &loader = CubicMeshLoader::getInstance();
		CubicMesh *coarseMesh = new CubicMesh();
		coarseMesh->setId("666");
		coarseMesh->setRheologyModel(model);
		loader.loadCoarseMesh(coarseMesh, prop.geometry, prop.coarseSpatialStep);
		
		InertiaMomentPartitioner part;
		real *proportions = new real[5];
		proportions[0] = 1;
		proportions[1] = 1;
		proportions[2] = 1;
		proportions[3] = 1;
		proportions[4] = 4;
		part.partMesh(this, coarseMesh, 5, proportions);
		for(uint i = 0; i < meshes.size(); i++) {
			std::cout << meshes[i]->getOutline() << meshes[i]->getNodesNumber() << std::endl;
			CubicMesh *fineMesh = new CubicMesh();
			fineMesh->setRheologyModel(model);
			loader.loadFineMeshFromCoarse(static_cast<CubicMesh *> (meshes[i]),
			                              fineMesh, prop.spatialStep);
			fineMesh->setId(to_string(i));
			meshes[i] = fineMesh;
			std::cout << meshes[i]->getOutline() << meshes[i]->getNodesNumber() << std::endl;
		}

	} else if (prop.meshType == "TetrahedronMesh") {
		uint nparts = 2;
		TetrMeshFirstOrder* coarseMesh = new TetrMeshFirstOrder();
		coarseMesh->setId("999");
		coarseMesh->setRheologyModel(model);
		TetrahedronMeshLoader::getInstance().loadMesh(coarseMesh, "models/cube.geo", prop.spatialStep);

		TetrMeshFirstOrder* coarsePart = new TetrMeshFirstOrder [nparts];
		MetisPartitioner::getInstance().partMesh(coarseMesh, nparts, coarsePart);

		//delete[] coarsePart;
		//delete coarseMesh;
	} else if (prop.meshType == "CubicMesh_Metis") {
		uint nparts = 2;
		CubicMesh* coarseMesh = new CubicMesh();
		coarseMesh->setId("666");
		coarseMesh->setRheologyModel(model);

		CubicMeshLoader& loader = CubicMeshLoader::getInstance();
		loader.loadCoarseMesh(coarseMesh, prop.geometry, prop.coarseSpatialStep);

		CubicMesh* coarsePart = new CubicMesh [nparts];
		MetisPartitioner::getInstance().partMesh(coarseMesh, nparts, coarsePart);
		for(uint i = 0; i < nparts; i++) {
			CubicMesh* fineMesh = new CubicMesh();
			fineMesh->setId(to_string(2000 + i));
			fineMesh->setRheologyModel(model);
			loader.loadFineMeshFromCoarse(&coarsePart[i], fineMesh, prop.spatialStep);

			this->addMesh(fineMesh);
		}

		//delete[] coarsePart;
	}
}

void Block::addMesh(Mesh* mesh) {
	meshes.push_back(mesh);
}

void Block::doNextTimeStep() {
	for(auto mesh = meshes.begin(); mesh != meshes.end(); mesh++) {
		solver->doNextTimeStep(*mesh);
		(*mesh)->snapshot(1);
	}
}

void Block::checkTopology(real tau)
{
	for(auto mesh = meshes.begin(); mesh != meshes.end(); mesh++)
		(*mesh)->checkTopology(tau);
}
