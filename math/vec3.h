#ifndef MATH_VEC3_H
#define MATH_VEC3_H

class Vec3 {
  float i_;
  float j_;
  float k_;

public:
  Vec3();
  Vec3(float i, float j, float k);
  float i() const;
  void set_i(float i);
  float j() const;
  void set_j(float j);
  float k() const;
  void set_k(float k);
  float Magnitude() const;
  Vec3 operator+(const Vec3& v) const;
  Vec3 operator-(const Vec3& v) const;
  Vec3 operator*(float value) const;
  static Vec3 Normalize(const Vec3& v);
  static Vec3 Cross(const Vec3& v1, const Vec3& v2);
  static float Dot(const Vec3& v1, const Vec3& v2);
};

#endif
