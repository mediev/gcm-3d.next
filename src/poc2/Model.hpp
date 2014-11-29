#ifndef MODEL_HPP
#define	MODEL_HPP

class Model {
public:
	virtual unsigned char getSizeOfVectorInPDE() = 0;
	virtual unsigned char getSizeOfValuesInODEs() = 0;
};

class ModelOne : public Model {
	static const unsigned char sizeOfVectorInPDE = 9;
	static const unsigned char sizeOfValuesInODEs = 0;
public:
	ModelOne();
	unsigned char getSizeOfVectorInPDE() {return sizeOfVectorInPDE;};
	unsigned char getSizeOfValuesInODEs() {return sizeOfValuesInODEs;};
};

class ModelTwo : public Model {
	static const unsigned char sizeOfVectorInPDE = 10;
	static const unsigned char sizeOfValuesInODEs = 2;
public:
	ModelTwo();
	unsigned char getSizeOfVectorInPDE() {return sizeOfVectorInPDE;};
	unsigned char getSizeOfValuesInODEs() {return sizeOfValuesInODEs;};
};

class ModelThree : public Model {
	static const unsigned char sizeOfVectorInPDE = 21;
	static const unsigned char sizeOfValuesInODEs = 5;
public:
	ModelThree();
	unsigned char getSizeOfVectorInPDE() {return sizeOfVectorInPDE;};
	unsigned char getSizeOfValuesInODEs() {return sizeOfValuesInODEs;};
};

#endif	/* MODEL_HPP */

