#ifndef NODES_HPP
#define NODES_HPP 1

using namespace std;

#include <vector>
#include <iostream>

class Node
{
	public:
		union
		{
			double coords[3];
			struct
			{
				double x;
				double y;
				double z;
			};
		};
			
		Node();
		Node(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};
		virtual ~Node();
};

class FirstNode : public Node
{
	public:
		static int VALUES_NUMBER;
		vector<double> values = vector<double>(9);
		
		FirstNode();
		FirstNode(double _x, double _y, double _z, const vector<double>& _values) : Node(_x, _y, _z), values(_values) {};
		~FirstNode();
};

class SecondNode : public Node
{
	public:
		static int VALUES_NUMBER;
		vector<double> values = vector<double>(10);
		
		SecondNode();
		SecondNode(double _x, double _y, double _z, const vector<double>& _values) : Node(_x, _y, _z), values(_values) {};
		~SecondNode();
};

class ThirdNode : public Node
{
	public:
		static int VALUES_NUMBER;
		vector<double> values = vector<double>(21);
		
		ThirdNode();
		ThirdNode(double _x, double _y, double _z, const vector<double>& _values) : Node(_x, _y, _z), values(_values) {};
		~ThirdNode();
};

#endif
