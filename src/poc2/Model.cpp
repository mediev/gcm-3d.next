#include "Model.hpp"


ModelOne::ModelOne() {
	modelName = "ModelOne";
	printf("ModelOne();\tNodeType = %d\n", getNodeType());
}


ModelTwo::ModelTwo() {
	modelName = "ModelTwo";
	printf("ModelTwo();\tNodeType = %d\n", getNodeType());
}

ModelThree::ModelThree() {
	modelName = "ModelThree";
	printf("ModelThree();\tNodeType = %d\n", getNodeType());
}

const char*Model::getName() {
	return modelName;
}