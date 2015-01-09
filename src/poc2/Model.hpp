#ifndef MODEL_HPP
#define	MODEL_HPP

#include <array>
#include <stdio.h>
#include "Node.hpp"

class GcmMatrix {
	unsigned char size;
	double** p;
public:
	GcmMatrix(const unsigned char size) {
		this->size = size;
		p = new double*[size];
		for(int i = 0; i < size; i++)
			p[i] = new double[size];
	};
	~GcmMatrix() {
		for(int i = 0; i < size; i++) {
			delete[] p[i];
		}
		delete[] p;
	};
	unsigned char getSize() {
		return size;
	};
	double operator()(unsigned char i, unsigned char j) {
		return p[i][j];
	};
};

class RheologyMatrix {
	unsigned char TYPE;
	GcmMatrix* a;
public:
	RheologyMatrix(unsigned char size) {
		printf("Create new GcmMatrix. Size = %d\n", size);
		a = new GcmMatrix(size);
	}
	virtual void decompose() = 0;
	GcmMatrix* getA() {
		return a;
	}
};

class ModelOneRheologyMatrix : public RheologyMatrix {
public:
	ModelOneRheologyMatrix() : RheologyMatrix(9) {};
	void decompose() {
		printf("decomposition of ModelOneRheologyMatrix\n");
	};
};

class ModelTwoRheologyMatrix : public RheologyMatrix {
public:
	ModelTwoRheologyMatrix() : RheologyMatrix(11) {};
	void decompose() {
		printf("decomposition of ModelTwoRheologyMatrix\n");
	};
};

class ModelThreeRheologyMatrix : public RheologyMatrix {
public:
	ModelThreeRheologyMatrix() : RheologyMatrix(11) {};
	void decompose() {
		printf("decomposition of ModelThreeRheologyMatrix\n");
	};
};


class Model {
protected:
	const char *modelName;
	RheologyMatrix* matrix;
public:
	const char *getName();
	
	RheologyMatrix* getRheologyMatrix() {
		return matrix;
	}
	
	virtual unsigned char getNodeType() = 0;
};


class ModelOne : public Model {
public:
	ModelOne();
	
	unsigned char getNodeType() {return DEFAULT_NODE_TYPE;};
};

class ModelTwo : public Model {
public:
	ModelTwo();
	
	unsigned char getNodeType() {return CUSTOM_NODE_TYPE;};
};

class ModelThree : public Model {
public:
	ModelThree();
	
	unsigned char getNodeType() {return ANOTHER_CUSTOM_NODE_TYPE;};
};

#endif	/* MODEL_HPP */