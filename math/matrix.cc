#include "matrix.h"
#include <cmath>
#include "math.h"
#include "vec3.h"
#include "vec4.h"

#include <cstdio>
#include <string>

Matrix::Matrix() {
  for (auto i = 0; i < 16; ++i) data_[i] = 0;
}

Matrix::Matrix(float initial_value) {
  for (auto i = 0; i < 16; ++i) data_[i] = initial_value;
}

Matrix::Matrix(float a0, float a4, float a8, float a12,
               float a1, float a5, float a9, float a13,
               float a2, float a6, float a10, float a14,
               float a3, float a7, float a11, float a15) {
  data_[0] = a0;
  data_[1] = a1;
  data_[2] = a2;
  data_[3] = a3;
  data_[4] = a4;
  data_[5] = a5;
  data_[6] = a6;
  data_[7] = a7;
  data_[8] = a8;
  data_[9] = a9;
  data_[10] = a10;
  data_[11] = a11;
  data_[12] = a12;
  data_[13] = a13;
  data_[14] = a14;
  data_[15] = a15;
}

Matrix::Matrix(const Matrix& m) {
  data_[0] = m[0];
  data_[1] = m[1];
  data_[2] = m[2];
  data_[3] = m[3];
  data_[4] = m[4];
  data_[5] = m[5];
  data_[6] = m[6];
  data_[7] = m[7];
  data_[8] = m[8];
  data_[9] = m[9];
  data_[10] = m[10];
  data_[11] = m[11];
  data_[12] = m[12];
  data_[13] = m[13];
  data_[14] = m[14];
  data_[15] = m[15];
}

const float* Matrix::data() const {
  return data_;
}

float* Matrix::data() {
  return data_;
}

float Matrix::Get(int row, int col) const {
  if (row < 0) return 0.0;
  if (row > 3) return 0.0;
  if (col > 3) return 0.0;
  if (col > 3) return 0.0;
  return data_[(4 * col) + row];
}

void Matrix::Set(int row, int col, float value) {
  if (row < 0) return;
  if (row > 3) return;
  if (col < 0) return;
  if (col > 3) return;
  data_[(4 * col) + row] = value;
}

void Matrix::Print() const {
  std::string format;
  format = "%5.1f %5.1f %5.1f %5.1f\n";
  format += "%5.1f %5.1f %5.1f %5.1f\n";
  format += "%5.1f %5.1f %5.1f %5.1f\n";
  format += "%5.1f %5.1f %5.1f %5.1f\n";
  std::printf(format.c_str(),
              Get(0,0), Get(0, 1), Get(0, 2), Get(0, 3),
              Get(1,0), Get(1, 1), Get(1, 2), Get(1, 3),
              Get(2,0), Get(2, 1), Get(2, 2), Get(2, 3),
              Get(3,0), Get(3, 1), Get(3, 2), Get(3, 3));
  std::puts("");
}

const float& Matrix::operator[](int index) const {
  return data_[index];
}

float& Matrix::operator[](int index) {
  return data_[index];
}

Matrix Matrix::operator*(const Matrix& m) const {
  Matrix out { 0 };
  for (auto i = 0; i < 4; ++i) {
    for (auto j = 0; j < 4; ++j) {
      float result = Get(i, 0) * m.Get(0, j) +
                     Get(i, 1) * m.Get(1, j) +
                     Get(i, 2) * m.Get(2, j) +
                     Get(i, 3) * m.Get(3, j);
      out.Set(i, j, result);
    }
  }

  return out;
}

Matrix Matrix::operator*(float value) const {
  Matrix out;
  for (auto i = 0; i < 16; ++i) out[i] = data_[i] * value;
  return out;
}

Vec4 Matrix::operator*(const Vec4& v) const {
  auto i = Get(0, 0) * v.i() +
           Get(0, 1) * v.j() +
           Get(0, 2) * v.k() +
           Get(0, 3) * v.w();
  auto j = Get(1, 0) * v.i() +
           Get(1, 1) * v.j() +
           Get(1, 2) * v.k() +
           Get(1, 3) * v.w();
  auto k = Get(2, 0) * v.i() +
           Get(2, 1) * v.j() +
           Get(2, 2) * v.k() +
           Get(2, 3) * v.w();
  auto w = Get(3, 0) * v.i() +
           Get(3, 1) * v.j() +
           Get(3, 2) * v.k() +
           Get(3, 3) * v.w();
  return { i, j, k, w };
}

Matrix Matrix::Identity() {
  return Matrix {
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  };
}

Matrix Matrix::Projection(float fovx, float aspect, float near, float far) {
  Matrix out { 0 };
  aspect = 1.0 / aspect;
  float f { static_cast<float>(1.0 / std::tan(ToRadians(fovx / 2.0))) };
  out.Set(0, 0, f);
  out.Set(1, 1, f / aspect);
  out.Set(2, 2, (far + near) / (near - far));
  out.Set(2, 3, (2 * far * near) / (near - far));
  out.Set(3, 2, -1);
  return out;
}

Matrix Matrix::Translate(float x, float y, float z) {
  auto out = Identity();
  out.Set(0, 3, x);
  out.Set(1, 3, y);
  out.Set(2, 3, z);
  return out;
}

Matrix Matrix::RotateX(float x) {
  auto x_rot = Identity();
  auto x_sin = static_cast<float>(std::sin(ToRadians(x)));
  auto x_cos = static_cast<float>(std::cos(ToRadians(x)));
  x_rot.Set(1, 1, x_cos);
  x_rot.Set(1, 2, -x_sin);
  x_rot.Set(2, 1, x_sin);
  x_rot.Set(2, 2, x_cos);
  return x_rot;
}

Matrix Matrix::RotateY(float y) {
  auto y_rot = Identity();
  auto y_sin = static_cast<float>(std::sin(ToRadians(y)));
  auto y_cos = static_cast<float>(std::cos(ToRadians(y)));
  y_rot.Set(0, 0, y_cos);
  y_rot.Set(0, 2, y_sin);
  y_rot.Set(2, 0, -y_sin);
  y_rot.Set(2, 2, y_cos);
  return y_rot;
}

Matrix Matrix::RotateZ(float z) {
  auto z_rot = Identity();
  auto z_sin = static_cast<float>(std::sin(ToRadians(z)));
  auto z_cos = static_cast<float>(std::cos(ToRadians(z)));
  z_rot.Set(0, 0, z_cos);
  z_rot.Set(0, 1, -z_sin);
  z_rot.Set(1, 0, z_sin);
  z_rot.Set(1, 1, z_cos);
  return z_rot;
}

Matrix Matrix::Scale(float x, float y, float z) {
  auto out = Identity();
  out.Set(0, 0, x);
  out.Set(1, 1, y);
  out.Set(2, 2, z);
  return out;
}
