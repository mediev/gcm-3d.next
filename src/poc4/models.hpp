#ifndef MODELS_HPP
#define MODELS_HPP 1

class Model
{
public:
	
};

// Model uses 9 values from default CalcNode
class FirstModel : public Model
{
public:
	FirstModel();
};

// Model uses 10 values from default CalcNode
class SecondModel : public Model
{
public:
	SecondModel();
};

// Model uses custom nodes and 20 values
class ThirdModel : public Model
{
public:
	ThirdModel();
};

#endif
