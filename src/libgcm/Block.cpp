#include "Block.hpp"

using namespace gcm;

Block::Block(const BlockProperties& prop, Engine *_engine) {
	engine = _engine;
	model = engine->getRheologyModel(prop.modelType);
	solver = engine->getSolver(prop.solverType);
	if (prop.meshType == "CubicMesh") {
		CubicMesh *mesh = new CubicMesh();
		CubicMeshLoader loader;
		loader.loadMesh(mesh, prop.geometry, prop.spatialStep);
		meshes.push_back(mesh);
	} else if (prop.meshType == "TetrahedronMesh") {
		TetrahedronMesh *mesh = new TetrahedronMesh();
		TetrahedronMeshLoader loader;
		loader.loadMesh(mesh, "MeshFile.gmsh", prop.spatialStep);
		meshes.push_back(mesh);
	}
}

void Block::doNextTimeStep()
{
	for(auto mesh = meshes.begin(); mesh != meshes.end(); mesh++)
		solver->doNextTimeStep(*mesh);
}

void Block::checkTopology(real tau)
{
	for(auto mesh = meshes.begin(); mesh != meshes.end(); mesh++)
		(*mesh)->checkTopology(tau);
}
