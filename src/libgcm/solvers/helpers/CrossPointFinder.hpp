#ifndef CrossPointFinder_HPP
#define CrossPointFinder_HPP 

#include "libgcm/util/matrixes.hpp"
#include "libgcm/rheology/Material.hpp"
#include "libgcm/node/CalcNode.hpp"

#include <memory>

namespace gcm
{
    class CrossPointFinder
    {
        public:
            virtual ~CrossPointFinder() = 0;
            // TODO: think carefully about passing parameters and return value
            // - What direction and what characteristic we are working with now?
            // - Passing local basis for node?
            // - What should be returned taking into account interpolation method signatures?
            virtual void find(const CalcNode& curNode, /*RheologyMatrixPtr matrix,*/ 
                        /*const gcm::real tau,*/ /*????*/) = 0;
    };
}
#endif /* CrossPointFinder_HPP */