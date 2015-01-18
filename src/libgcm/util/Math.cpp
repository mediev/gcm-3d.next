#include "libgcm/util/Math.hpp"
#include "libgcm/util/Assertion.hpp"

#include <cmath>

using namespace gcm;

/*
 * P(x) = x^3 + a*x^2 + b*x + c
 * All the roots are real
 * See http://ru.wikipedia.org/wiki/Тригонометрическая_формула_Виета for algo
 */
void solvePolynomialThirdOrder(double a, double b, double c, double& root1, double& root2, double& root3)
{
    long double p = b - a * a / 3.0;
    assert_lt(p, EQUALITY_TOLERANCE * (1 + fabs(b)));

    // Special case - all roots are equal
    if( fabs(p) < EQUALITY_TOLERANCE * (1 + fabs(b)))
    {
        root1 = root2 = root3 = - a / 3.0;
        return;
    }

    // All the other cases are covered with this algo
    long double q = 2.0 * a * a * a / 27.0 - a * b / 3.0 + c;
    long double A = sqrt(-4.0 * p / 3.0);
	
    long double c3phi = -4.0 * q / (A * A * A);
	if( fabs(c3phi) > 1 - 1e-10 * EQUALITY_TOLERANCE )
		c3phi = (c3phi > 0 ? 1.0 : -1.0);
	
    long double phi = acos(c3phi) / 3.0;

    root1 = A * cos(phi) - a / 3.0;
    root2 = A * cos(phi + 2 * M_PI / 3.0) - a / 3.0;
    root3 = A * cos(phi - 2 * M_PI / 3.0) - a / 3.0;
};