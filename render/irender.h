#ifndef RENDER_IRENDER_H
#define RENDER_IRENDER_H

#include <string>
#include "imodel.h"
#include "../math/vec3.h"
#include "../window/iwindow.h"

class IRender {
public:
  virtual ~IRender() = 0;
  virtual bool Initialize() = 0;
  virtual void Update() = 0;
  virtual void LoadData(const std::string& filepath) = 0;
  virtual void UnloadData() = 0;
  virtual void SetBackgroundColor(float r, float g, float b, float a) = 0;
  virtual void SetCameraProjection(const Matrix& projection) = 0;
  virtual void SetCameraPosition(const Vec3& position) = 0;
  virtual void SetCameraDirection(const Vec3& location) = 0;
  virtual void CameraLookat(const Vec3& location) = 0;
  virtual void DrawModel(IModel* model) = 0;
};

#endif
