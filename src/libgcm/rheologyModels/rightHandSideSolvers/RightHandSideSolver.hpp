#ifndef RightHandSideSolver_HPP
#define RightHandSideSolver_HPP 

#include "libgcm/util/matrixes.hpp"
#include "libgcm/rheology/Material.hpp"
#include "libgcm/node/CalcNode.hpp"

#include <memory>

namespace gcm
{
    class RightHandSideSolver
    {
        public:
            virtual ~RightHandSideSolver() = 0;
            virtual void solver(const CalcNode& curNode, CalcNode& newNode, 
                        const gcm::real tau, const GcmVector& f) = 0;
    };
}
#endif /* RightHandSideSolver_HPP */