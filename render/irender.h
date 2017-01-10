#ifndef RENDER_IRENDER_H
#define RENDER_IRENDER_H

#include <functional>
#include <string>
#include "imodel.h"
#include "../math/vec3.h"
#include "../math/matrix.h"

class IRender {
public:
  virtual ~IRender() = 0;
  virtual bool Initialize() = 0;
  virtual std::function<void(int,int)> GetResizeFunction() = 0;
  virtual void Update() = 0;
  virtual void LoadData(const std::string& filepath) = 0;
  virtual void UnloadData() = 0;
  virtual void SetBackgroundColor(float r, float g, float b, float a) = 0;
  virtual const Matrix& camera_projection() const = 0;
  virtual void set_camera_projection(const Matrix& projection) = 0;
  virtual const Vec3& camera_position() const = 0;
  virtual void set_camera_position(const Vec3& position) = 0;
  virtual const Vec3& camera_direction() const = 0;
  virtual void set_camera_direction(const Vec3& direction) = 0;
  virtual void CameraLookat(const Vec3& location) = 0;
  virtual void DrawModel(IModel* model) = 0;
};

#endif
