#include "Model.hpp"


ModelOne::ModelOne() {
	modelName = "ModelOne";
	printf("ModelOne();\tSizeOfVectorInPDE = %d\n", sizeOfVectorInPDE);
}


ModelTwo::ModelTwo() {
	modelName = "ModelTwo";
	printf("ModelTwo();\tSizeOfVectorInPDE = %d\n", sizeOfVectorInPDE);
}

ModelThree::ModelThree() {
	modelName = "ModelThree";
	printf("ModelThree();\tSizeOfVectorInPDE = %d\n", sizeOfVectorInPDE);
}

const char*Model::getName() {
	return modelName;
}