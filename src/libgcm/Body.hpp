#ifndef BODY_HPP
#define	BODY_HPP

#include "libgcm/Launcher.hpp"
#include "Block.hpp"

namespace gcm {
	class Engine;
	class Block;
	struct BodyProperties;
	
	class Body {
	protected:
		uint id;
		std::vector<Block*> blocks;
	public:
		Body();
		void loadTask(const BodyProperties &prop);
		void checkTopology();
		void doNextTimeStep();
		void setId(uint _id);
		uint getId();
	};
}
#endif	/* BODY_HPP */
