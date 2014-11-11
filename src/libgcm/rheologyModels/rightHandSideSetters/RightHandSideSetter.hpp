#ifndef RightHandSideSetter_HPP
#define RightHandSideSetter_HPP 

#include "libgcm/util/matrixes.hpp"
#include "libgcm/rheology/Material.hpp"
#include "libgcm/node/CalcNode.hpp"

#include <memory>

namespace gcm
{
    class RightHandSideSetter
    {
        public:
            virtual ~RightHandSideSetter() = 0;
            virtual void setVector(GcmVector& f, const MaterialPtr& material, const CalcNode& node) = 0;
    };
}
#endif /* RightHandSideSetter_HPP */