#include "models.hpp"
#include "nodes.hpp"

FirstModel::FirstModel()
{
	FirstNode::VALUES_NUMBER = 9;
	cout << "FirstModel: loaded" << endl;
}

SecondModel::SecondModel()
{
	SecondNode::VALUES_NUMBER = 10;
	cout << "SecondModel: loaded" << endl;
}

ThirdModel::ThirdModel()
{
	ThirdNode::VALUES_NUMBER = 21;
	cout << "ThirdModel: loaded" << endl;
}
