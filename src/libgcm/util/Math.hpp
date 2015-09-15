#ifndef GCM_MATH_H
#define GCM_MATH_H

#include <cmath>
#include <cassert>
#include <cstring>
#include "libgcm/util/Types.hpp"
#include "libgcm/util/Vector3.hpp"
#include "libgcm/util/Assertion.hpp"

using namespace gcm;

/*void solvePolynomialThirdOrder(double a, double b, double c,
            double& root1, double& root2, double& root3);
inline real solidAngle(const vector3r& v1, const vector3r& v2, const vector3r& v3);
inline real determinant(const vector3r& v1, const vector3r& v2, const vector3r& v3);
inline real determinant(real x1, real y1, real z1, real x2, real y2, real z2, real x3, real y3, real z3);
inline real tetrHeight(const vector3r& v0, const vector3r& v1, const vector3r& v2, const vector3r& v3);
inline real triArea(const vector3r& v1, const vector3r& v2);
inline real tetrVolume(const vector3r& v1, const vector3r& v2, const vector3r& v3);
inline void findTriangleFaceNormal(const vector3r& p1, const vector3r& p2, const vector3r& p3, vector3r& result);
inline bool pointInTetr(const vector3r& v, const vector3r& v0, const vector3r& v1, const vector3r& v2, const vector3r& v3);
inline void shiftArrayLeft(uint* arr, int n);
inline real distance(const vector3r* a, const vector3r* b);
*/
/*
 * P(x) = x^3 + a*x^2 + b*x + c
 * All the roots are real
 * See http://ru.wikipedia.org/wiki/Тригонометрическая_формула_Виета for algo
 */
inline void solvePolynomialThirdOrder(double a, double b, double c, 
                                      double& root1, double& root2, double& root3)
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

inline real determinant(const vector3r& v1, const vector3r& v2, const vector3r& v3)
{
	return (v1[0]*(v2[1]*v3[2]-v3[1]*v2[2]) - v2[0]*(v1[1]*v3[2]-v3[1]*v1[2]) + v3[0]*(v1[1]*v2[2]-v2[1]*v1[2]));
};

inline real determinant(real x1, real y1, real z1, real x2, real y2, real z2, real x3, real y3, real z3)
{
    return (x1*(y2*z3-y3*z2) - x2*(y1*z3-y3*z1) + x3*(y1*z2-y2*z1));
};

inline real triArea(const vector3r& v1, const vector3r& v2)
{
	real diff = (v1 * v1) * (v2 * v2) - (v1 * v2) * (v1 * v2);
    if(diff < 0.0)
        return 0.0;
    return sqrt(diff)/2.0;
};

inline real tetrVolume(const vector3r& v1, const vector3r& v2, const vector3r& v3)
{
    return determinant(v1, v2, v3) / 6.0;
};

inline real solidAngle(const vector3r& v1, const vector3r& v2, const vector3r& v3)
{
	real det = fabs( determinant(v1, v2, v3) );
    real norm_v1 = sqrt(v1 * v1);
    real norm_v2 = sqrt(v2 * v2);
    real norm_v3 = sqrt(v3 * v3);
    real div = norm_v1 * norm_v2 * norm_v3 + (v1 * v2) * norm_v3 + (v1 * v3) * norm_v2 + (v2 * v3) * norm_v1;
    real at = atanf( det / div );
    if (at < 0)
        at += M_PI;

    return 2 * at;
};

inline real tetrHeight(const vector3r& v0, const vector3r& v1, const vector3r& v2, const vector3r& v3)
{
    real area[4];
    real maxArea;

    // Find volume
    real vol = fabs( tetrVolume( v1 - v0, v2 - v0, v3 - v0));

    // Find area of first face (verticles - 0,1,2)
    area[0] = triArea(v1 - v0, v2 - v0);
    // Find area of second face (verticles - 0,1,3)
    area[1] = triArea(v1 - v0, v3 - v0);
    // Find area of third face (verticles - 0,2,3)
    area[2] = triArea(v2 - v0, v3 - v0);
    // Find area of third face (verticles - 1,2,3)
    area[3] = triArea(v2 - v1, v3 - v1);

    // Check if all nodes are already loaded from other CPUs and tetrahadron is correct
    assert(vol > 0);
    for(int j = 0; j < 4; j++)
        assert(area[j] > 0);

    // Find maximum face area
    maxArea = area[0];
    for(int j = 1; j < 4; j++)
        if( area[j] > maxArea )
            maxArea = area[j];

    // Return minumal height of this tetrahedron
    return fabs( 3 * vol / maxArea );

};

inline void findTriangleFaceNormal(const vector3r& p1, const vector3r& p2, const vector3r& p3, vector3r& result)
{
    // Normal vector
    vector3r normal;

    normal = vecProduct(p2 - p1, p3 - p1);

    result = normal / sqrt(normal * normal);
};

inline bool pointInTetr(const vector3r& v, const vector3r& v0, const vector3r& v1, const vector3r& v2, const vector3r& v3)
{
    real vol;
    real vols[4];

    vol = fabs( determinant(v1 - v0, v2 - v0, v3 - v0) );

    vols[0] = fabs( determinant(v1 - v, v2 - v, v3 - v) );
    vols[1] = fabs( determinant(v0 - v, v2 - v, v3 - v) );
    vols[2] = fabs( determinant(v1 - v, v0 - v, v3 - v) );
    vols[3] = fabs( determinant(v1 - v, v2 - v, v0 - v) );

    if( vols[0] + vols[1] + vols[2] + vols[3] < vol * (1 + 10 * EQUALITY_TOLERANCE) ) {
        return true;
    } else {
        return false;
    }
};

inline void shiftArrayLeft(uint* arr, int n)
{
	assert(n > 0);
	uint a0 = arr[0];
	memmove(arr, arr+1, (n-1) * sizeof(uint));
	arr[n-1] = a0;
};

inline real distance(const vector3r& a, const vector3r& b)
{
    return sqrt( a * b );
};

inline int realToInt(const real &x)
{
	if ( (x - (int) x) < 0.5 ) return (int) x;
	return (int) x + 1;
};

inline char signum(const real& x)
{
	if (x < 0) return -1;
	if (x == 0) return 0;
	return 1;
};

#endif    /* GCM_MATH_H */
