#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H

#include "vec3.h"
#include "vec4.h"

class Matrix {
  float data_[16];

public:
  Matrix();
  Matrix(float initial_value);
  Matrix(float a0, float a4, float a8, float a12,
         float a1, float a5, float a9, float a13,
         float a2, float a6, float a10, float a14,
         float a3, float a7, float a11, float a15);
  Matrix(const Matrix& m);
  const float* data() const;
  float* data();
  float Get(int row, int col) const;
  void Set(int row, int col, float value);
  void Print() const;
  const float& operator[](int index) const;
  float& operator[](int index);
  Matrix operator*(const Matrix& m) const;
  Matrix operator*(float value) const;
  Vec4 operator*(const Vec4& v) const;
  static Matrix Identity();
  static Matrix Projection(float fovy, float aspect, float near, float far);
  static Matrix Translate(float x, float y, float z);
  static Matrix RotateX(float x);
  static Matrix RotateY(float y);
  static Matrix RotateZ(float z);
  static Matrix Scale(float x, float y, float z);
};

#endif
