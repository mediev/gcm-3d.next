#ifndef GCM_MATH_H
#define GCM_MATH_H

#include "libgcm/util/Types.hpp"

namespace gcm
{
    void solvePolynomialThirdOrder(gcm::real a, gcm::real b, gcm::real c, 
            gcm::real& root1, gcm::real& root2, gcm::real& root3);
}
#endif    /* GCM_MATH_H */