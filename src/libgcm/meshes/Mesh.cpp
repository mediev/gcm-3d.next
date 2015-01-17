#include "libgcm/meshes/Mesh.hpp"


using namespace gcm;

void Mesh::setRheologyModel(RheologyModel* _model) {
	rheologyModel = _model;
}

RheologyModel *Mesh::getRheologyModel() {
	return rheologyModel;
}
