#include "vec3.h"
#include <cmath>
#include "math.h"

Vec3::Vec3()
    : i_ { 0.0 },
      j_ { 0.0 },
      k_ { 0.0 }
{}

Vec3::Vec3(float i, float j, float k)
    : i_ { i },
      j_ { j },
      k_ { k }
{}

float Vec3::i() const {
    return i_;
}

void Vec3::set_i(float i) {
    i_ = i;
}

float Vec3::j() const {
    return j_;
}

void Vec3::set_j(float j) {
    j_ = j;
}

float Vec3::k() const {
    return k_;
}

void Vec3::set_k(float k) {
    k_ = k;
}

float Vec3::Magnitude() const {
    auto magnitude = std::sqrt(std::pow(i_, 2) +
                               std::pow(j_, 2) +
                               std::pow(k_, 2));
    return magnitude;
}

Vec3 Vec3::operator+(const Vec3& v) const {
    Vec3 out {
        i_ + v.i(),
        j_ + v.j(),
        k_ + v.k()
    };
    return out;
}

Vec3 Vec3::operator-(const Vec3& v) const {
    Vec3 out {
        i_ - v.i(),
        j_ - v.j(),
        k_ - v.k()
    };
    return out;
}

Vec3 Vec3::operator*(float value) const {
    Vec3 out {
        i_ * value,
        j_ * value,
        k_ * value
    };
    return out;
}

Vec3 Vec3::Normalize(const Vec3& v) {
    auto magnitude = v.Magnitude();
    if (feq(magnitude, 0)) return Vec3 {};
    Vec3 out {
        v.i() / magnitude,
        v.j() / magnitude,
        v.k() / magnitude,
    };
    return out;
}

Vec3 Vec3::Cross(const Vec3& v1, const Vec3& v2) {
    Vec3 out {
        (v1.j() * v2.k()) - (v1.k() * v2.j()),
        -((v1.i() * v2.k()) - (v1.k() * v2.i())),
        (v1.i() * v2.j()) - (v1.j() * v2.i())
    };
    return out;
}

float Vec3::Dot(const Vec3& v1, const Vec3& v2) {
    return (v1.i() * v2.i()) + (v1.j() * v2.j()) + (v1.k() * v2.k());
}
