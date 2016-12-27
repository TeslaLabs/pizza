#ifndef MATH_MATH_H
#define MATH_MATH_H

#include <cfloat>

#define feq(A, B) (std::fabs(A - B) < FLT_EPSILON)
#define ToRadians(degrees) (degrees / 180.0 * 3.14159265)

#endif
