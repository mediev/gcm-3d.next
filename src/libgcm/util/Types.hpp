#ifndef GCM_TYPES
#define GCM_TYPES

#include "libgcm/util/Assertion.hpp"

#include <cmath>

namespace gcm
{
    
    #ifndef GCM_DOUBLE_PRECISION
    typedef float real;
    #else
    typedef double real;
    #endif    
    
    typedef unsigned char uchar;
    typedef unsigned int uint;
    typedef unsigned long ulong;
}
#endif
