#ifndef GCM_MATH_H
#define GCM_MATH_H

#include <cmath>
#include "libgcm/util/Types.hpp"
#include "libgcm/util/Assertion.hpp"


namespace gcm
{
    void solvePolynomialThirdOrder(double a, double b, double c, 
            double& root1, double& root2, double& root3);
}
#endif    /* GCM_MATH_H */