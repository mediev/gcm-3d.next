#include "Model.hpp"


ModelOne::ModelOne() {
	modelName = "ModelOne";
        matrix = new ModelOneRheologyMatrix();
	printf("ModelOne();\tNodeType = %d\n", getNodeType());
}

std::string ModelOne::getType()
{
	return "ModelOne";
}

ModelTwo::ModelTwo() {
	modelName = "ModelTwo";
        matrix = new ModelTwoRheologyMatrix();
	printf("ModelTwo();\tNodeType = %d\n", getNodeType());
}

std::string ModelTwo::getType()
{
	return "ModelTwo";
}

ModelThree::ModelThree() {
	modelName = "ModelThree";
        matrix = new ModelThreeRheologyMatrix();
	printf("ModelThree();\tNodeType = %d\n", getNodeType());
}

std::string ModelThree::getType()
{
	return "ModelThree";
}
