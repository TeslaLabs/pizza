#ifndef RENDER_IMODEL_H
#define RENDER_IMODEL_H

#include <string>
#include "../math/matrix.h"

class IModel {
public:
  virtual const std::string& name() const = 0;
  virtual const std::string& shader_name() const = 0;
  virtual const Vec3& position() const = 0;
  virtual void set_position(const Vec3& position) = 0;
  virtual const Vec3& rotation() const = 0;
  virtual void set_rotation(const Vec3& rotation) = 0;
  virtual const Vec3& scale() const = 0;
  virtual void set_scale(const Vec3& scale) = 0;
};

#endif
