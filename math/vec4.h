#ifndef MATH_VEC4_H
#define MATH_VEC4_H

#include "vec3.h"

class Vec4 {
    float i_;
    float j_;
    float k_;
    float w_;

public:
    Vec4();
    Vec4(float i, float j, float k, float w);
    Vec4(const Vec3& v, float w);
    float i() const;
    void set_i(float i);
    float j() const;
    void set_j(float j);
    float k() const;
    void set_k(float k);
    float w() const;
    void set_w(float w);
    Vec3 ijk() const;
};

#endif
