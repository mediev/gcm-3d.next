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
		std::vector<Block*> blocks;
	public:
		Body(const BodyProperties &prop);
		void checkTopology();
		void doNextTimeStep();
	};
}
#endif	/* BODY_HPP */
