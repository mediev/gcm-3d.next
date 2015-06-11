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
		Engine *engine;
	public:
		Body(const BodyProperties &prop, Engine *_engine);
		void checkTopology();
		void doNextTimeStep();
	};
}
#endif	/* BODY_HPP */
