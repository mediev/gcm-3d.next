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
		proportions[1] = 2;
		proportions[2] = 3;
		proportions[3] = 4;
		proportions[4] = 5;
		part.partMesh(this, coarseMesh, 5, proportions);
		for(uint i = 0; i < meshes.size(); i++) {
			CubicMesh *fineMesh = new CubicMesh();
			fineMesh->setRheologyModel(model);
			loader.loadFineMeshFromCoarse(static_cast<CubicMesh *> (meshes[i]), 
			                              fineMesh, prop.spatialStep);
			meshes[i] = fineMesh;
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

void Block::doNextTimeStep()
{
	for(auto mesh = meshes.begin(); mesh != meshes.end(); mesh++) {
		solver->doNextTimeStep(*mesh);
		//(*mesh)->snapshot(1);
	}
}

void Block::checkTopology(real tau)
{
	for(auto mesh = meshes.begin(); mesh != meshes.end(); mesh++)
		(*mesh)->checkTopology(tau);
}
