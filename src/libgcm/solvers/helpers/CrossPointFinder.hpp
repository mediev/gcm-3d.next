#ifndef CrossPointFinder_HPP
#define CrossPointFinder_HPP 

#include "libgcm/rheologyModels/GcmMatrix.hpp"
#include "libgcm/rheologyModels/Material.hpp"
#include "libgcm/nodes/CalcNode.hpp"
#include "libgcm/util/Logging.hpp"
#include "libgcm/util/Vector3.hpp"
#include "libgcm/util/Types.hpp"

#include <memory>

namespace gcm
{
    class CrossPointFinder
    {
        public:
			CrossPointFinder();
            ~CrossPointFinder();
            // TODO: think carefully about passing parameters and return value
            // - What direction and what characteristic we are working with now?
            // - Passing local basis for node?
            // - What should be returned taking into account interpolation method signatures?
            /**
             * Finds coordinates of crossing points of characteritics and previous time layer
             * @param curNode Node where characteristics are let out
             * @param matrix RheologyMatrix for curNode
             * @param tau Time step
             * @param points Vector3r for writing found coordinates
             */
            virtual void find(const CalcNode& curNode, RheologyMatrixPtr matrix, const gcm::real tau, vector3r* points) = 0;
            /**
             * Finds coordinates of crossing point of the one characteritic and previous time layer
             * @param curNode Node where characteristics are let out
             * @param matrix RheologyMatrix for curNode
             * @param tau Time step
             * @param num Sequence number of the characteritic
             */
			virtual vector3r find(const CalcNode& curNode, RheologyMatrixPtr matrix, const gcm::real tau, int num) = 0;
    };
}
#endif /* CrossPointFinder_HPP */