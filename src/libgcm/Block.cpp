#include "Block.hpp"

using namespace gcm;

Block::Block() {
}

void Block::loadTask(const BlockProperties& prop) {
	Engine& engine = Engine::getInstance();
	model = engine.getRheologyModel(prop.modelType);
	solver = engine.getSolver(prop.solverType);

	if (prop.meshType == "CubicMesh") {
		CubicMeshLoader &loader = CubicMeshLoader::getInstance();
		CubicMesh *coarseMesh = new CubicMesh();
		coarseMesh->setId("testMesh");
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
			meshes[i] = fineMesh;
			std::cout << meshes[i]->getOutline() << meshes[i]->getNodesNumber() << std::endl;
		}

	} else if (prop.meshType == "TetrahedronMesh") {
		TetrMeshFirstOrder* mesh = new TetrMeshFirstOrder();
		mesh->setId("testMesh");
		mesh->setRheologyModel(model);

		TetrahedronMeshLoader::getInstance().loadMesh(mesh, "models/cube.geo", prop.spatialStep);
		meshes.push_back(mesh);
	}
}

void Block::addMesh(Mesh* mesh) {
	meshes.push_back(mesh);
}

void Block::doNextTimeStep() {
	int i = 0;
	for(auto mesh = meshes.begin(); mesh != meshes.end(); mesh++) {
		solver->doNextTimeStep(*mesh);
		(*mesh)->snapshot(i);
		i++;
	}
}

void Block::checkTopology(real tau)
{
	for(auto mesh = meshes.begin(); mesh != meshes.end(); mesh++)
		(*mesh)->checkTopology(tau);
}
