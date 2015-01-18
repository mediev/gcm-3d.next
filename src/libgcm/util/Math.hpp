#ifndef GCM_MATH_H
#define GCM_MATH_H

#include "libgcm/util/Types.hpp"

namespace gcm
{
    void solvePolynomialThirdOrder(double a, double b, double c, 
            double& root1, double& root2, double& root3);
}
#endif    /* GCM_MATH_H */