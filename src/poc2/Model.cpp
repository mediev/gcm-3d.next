#include "Model.hpp"


ModelOne::ModelOne() {
	modelName = "ModelOne";
        matrix = new ModelOneRheologyMatrix();
	printf("ModelOne();\tNodeType = %d\n", getNodeType());
}


ModelTwo::ModelTwo() {
	modelName = "ModelTwo";
        matrix = new ModelTwoRheologyMatrix();
	printf("ModelTwo();\tNodeType = %d\n", getNodeType());
}

ModelThree::ModelThree() {
	modelName = "ModelThree";
        matrix = new ModelThreeRheologyMatrix();
	printf("ModelThree();\tNodeType = %d\n", getNodeType());
}

const char*Model::getName() {
	return modelName;
}