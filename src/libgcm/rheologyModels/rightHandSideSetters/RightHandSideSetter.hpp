#ifndef RightHandSideSetter_HPP
#define RightHandSideSetter_HPP 

#include "libgcm/rheologyModels/GcmMatrix.hpp"
#include "libgcm/rheologyModels/Material.hpp"

#include <memory>
#include <vector>

namespace gcm
{
    class RightHandSideSetter
    {
        public:
            virtual ~RightHandSideSetter() = 0;
            virtual void setVector(std::vector<int>/*FIXME*/& f, const MaterialPtr& material, const CalcNode& node) = 0;
    };
}
#endif /* RightHandSideSetter_HPP */