#include "Model.hpp"


ModelOne::ModelOne() {
	modelName = "ModelOne";
	printf("ModelOne();\tNodeType = %d\n", getNodeType());
}

std::string ModelOne::getType()
{
	return "ModelOne";
}

ModelTwo::ModelTwo() {
	modelName = "ModelTwo";
	printf("ModelTwo();\tNodeType = %d\n", getNodeType());
}

std::string ModelTwo::getType()
{
	return "ModelTwo";
}

ModelThree::ModelThree() {
	modelName = "ModelThree";
	printf("ModelThree();\tNodeType = %d\n", getNodeType());
}

std::string ModelThree::getType()
{
	return "ModelThree";
}
