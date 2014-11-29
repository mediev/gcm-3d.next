#include <stdio.h>

#include "Model.hpp"


ModelOne::ModelOne() {
	printf("ModelOne();\tSizeOfVectorInPDE = %d\n", sizeOfVectorInPDE);
}


ModelTwo::ModelTwo() {
	printf("ModelTwo();\tSizeOfVectorInPDE = %d\n", sizeOfVectorInPDE);
}


ModelThree::ModelThree() {
	printf("ModelThree();\tSizeOfVectorInPDE = %d\n", sizeOfVectorInPDE);
}
