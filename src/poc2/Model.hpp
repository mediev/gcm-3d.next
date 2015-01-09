#ifndef MODEL_HPP
#define	MODEL_HPP

#include <stdio.h>
#include "Node.hpp"

class Model {
protected:
	const char *modelName;
public:
	const char *getName();
	
	class RheologyMatrix {
		unsigned char TYPE;
	public:
		virtual void decompose() = 0;
	};
	virtual RheologyMatrix *getRheologyMatrix() = 0;
	virtual std::string getType() = 0;
	
	virtual unsigned char getNodeType() = 0;
};


class ModelOne : public Model {
public:
	ModelOne();
	
	class ModelOneRheologyMatrix : public RheologyMatrix {
		double matrix[9][9];
		public:
			void decompose() {	printf("decomposition of ModelOneRheologyMatrix\n"); };
	} modelOneRheologyMatrix;
	
	ModelOneRheologyMatrix* getRheologyMatrix() { return &modelOneRheologyMatrix; };
	
	unsigned char getNodeType() {return DEFAULT_NODE_TYPE;};
	std::string getType() override;
};

class ModelTwo : public Model {
public:
	ModelTwo();
	
	class ModelTwoRheologyMatrix : public RheologyMatrix {
		double matrix[11][11];
		public:
			void decompose() { printf("decomposition of ModelTwoRheologyMatrix\n");	};
	} modelTwoRheologyMatrix;
	
	ModelTwoRheologyMatrix* getRheologyMatrix() { return &modelTwoRheologyMatrix; };
	
	unsigned char getNodeType() {return CUSTOM_NODE_TYPE;};
	std::string getType() override;
};

class ModelThree : public Model {
public:
	ModelThree();
	
	class ModelThreeRheologyMatrix : public RheologyMatrix {
		double matrix[11][11];
		public:
			void decompose() { printf("decomposition of ModelThreeRheologyMatrix\n"); };
	} modelThreeRheologyMatrix;
	
	ModelThreeRheologyMatrix* getRheologyMatrix() {	return &modelThreeRheologyMatrix; };
	
	unsigned char getNodeType() {return ANOTHER_CUSTOM_NODE_TYPE;};
	std::string getType() override;
};

#endif	/* MODEL_HPP */
