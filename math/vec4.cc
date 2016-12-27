#include "vec4.h"
#include "vec3.h"

Vec4::Vec4()
    : i_ { 0 },
      j_ { 0 },
      k_ { 0 },
      w_ { 0 }
{}

Vec4::Vec4(float i, float j, float k, float w)
    : i_ { i },
      j_ { j },
      k_ { k },
      w_ { w }
{}

Vec4::Vec4(const Vec3& v, float w)
    : i_ { v.i() },
      j_ { v.j() },
      k_ { v.k() },
      w_ { w }
{}

float Vec4::i() const {
    return i_;
}

void Vec4::set_i(float i) {
    i_ = i;
}

float Vec4::j() const {
    return j_;
}

void Vec4::set_j(float j) {
    j_ = j;
}

float Vec4::k() const {
    return k_;
}

void Vec4::set_k(float k) {
    k_ = k;
}

float Vec4::w() const {
    return w_;
}

void Vec4::set_w(float w) {
    w_ = w;
}

Vec3 Vec4::ijk() const {
    return { i_, j_, k_ };
}
