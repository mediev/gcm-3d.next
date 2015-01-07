#ifndef BODY_HPP
#define	BODY_HPP

#include "Block.hpp"

class BodyConfig
{
	public:
		struct BlockConfig {
			struct Vertex {	double x;	double y;	double z; };
			Vertex vertices[8];
			std::string name;
			std::string meshType;
			std::string solverType;
			std::string modelType;
		};
		
		unsigned char blocksNum;
		BlockConfig* blocksConf;
		
		BodyConfig() { };
		BodyConfig(unsigned char _blocksNum) {
			blocksNum = _blocksNum;
			blocksConf = new BlockConfig [blocksNum];
		}
		~BodyConfig() {
			delete[] blocksConf;	
		}
};

class Body {
protected:
	BodyConfig* bodyConf;
	std::vector<Block> blocks;
public:
	Body(BodyConfig* _bodyConf) : bodyConf(_bodyConf) {};
	bool checkTopology();
	void doCalc();
	void load();
};

#endif	/* BODY_HPP */
