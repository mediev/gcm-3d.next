#ifndef BODY_HPP
#define	BODY_HPP

#include "Block.hpp"

class Body {
protected:
	std::vector<Block> blocks;
	double* container;
public:
	Body() {};
	~Body();
	bool checkTopology();
	void addBlock(Block block);
	void setModel(unsigned char i);
	void initContainer();
	void load(std::vector<CalcNode>& vertices);
	void doCalc();
};

#endif	/* BODY_HPP */
