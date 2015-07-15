#ifndef LAUNCHER_HPP
#define LAUNCHER_HPP

#include "libgcm/Engine.hpp"
#include "libgcm/util/Types.hpp"


namespace gcm {
	class Engine;
	
	/**
	 * Simple struct to imitate geo and msh files to describe geometry of object.
	 * Just cube now.
	 * Will be replaced by them later.
	 */
	struct Geometry {
		real x0, y0, z0; // min coords of cube's points
		real hx, hy, hz; // heights of cube by axis
		real getMinHeight() {
			real minH = (hx > hy) ? hy : hx;
			minH = (minH > hz) ? hz : minH;
			return minH;
		};
	};
	struct BlockProperties {
		// Relative to other blocks of this body computational cost of the block.
		// Used to distribute processors of the body among blocks of the body.
		real computationalCost; 
		uint id;
		std::string meshType;
		std::string modelType;
		std::string solverType;
		Geometry geometry;
		real spatialStep;
		real coarseSpatialStep;
		bool operator<(const BlockProperties &other) const {
			return computationalCost < other.computationalCost;
		}
	};
	struct BodyProperties {
		// Relative to other bodies of the task computational cost of the body.
		// Used to distribute processors of the program among bodies.
		real computationalCost;
		uint id;
		std::vector<BlockProperties> blocks; 
		bool operator<(const BodyProperties &other) const {
			return computationalCost < other.computationalCost;
		}
	};
	struct Task {
		real timeStep;
		real requiredTime;
		std::vector<BodyProperties> bodies;
	};

	class Launcher {
		public:
			Task task;
			Launcher();
			Launcher(const uint taskNum);

	};
}
#endif /* LAUNCHER_HPP */
