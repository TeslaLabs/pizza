#include "glrender.h"

GLRender::Camera::Camera()
  : projection { Matrix::Projection(90, 4.0 / 3.0, 1.0, 1000000.0) },
    position { Vec3 { 0, 0, 0 } },
    rotation { Vec3 { 0, 0, 0 } }
{}
