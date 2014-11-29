#ifndef MODELS
#define MODELS 1

#include <vector>
#include "nodes.hpp"
#include "mesh.hpp"

// Base model
class Model
{
public:
	
};

// Model uses 9 values from default CalcNode
class ModelOne : public Model
{
public:
	ModelOne();
};

// Model uses 10 values from default CalcNode
class ModelTwo : public Model
{
public:
	ModelTwo();
};

// Model uses custom nodes and 20 values
class ModelThree : public Model
{
public:
	ModelThree();
};

#endif
