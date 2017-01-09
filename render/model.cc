#include "model.h"
#include "../math/vec3.h"

Model::Model(const std::string& name,
             const std::string& shader_name)
  : name_ { name },
    shader_name_ { shader_name }
{}

const std::string& Model::name() const {
  return name_;
}

const std::string& Model::shader_name() const {
  return shader_name_;
}

void Model::set_shader(const std::string& shader_name) {
  shader_name_ = shader_name;
}

const Vec3& Model::position() const {
  return position_;
}

void Model::set_position(const Vec3& position) {
  position_ = position;
}

const Vec3& Model::rotation() const {
  return rotation_;
}

void Model::set_rotation(const Vec3& rotation) {
  rotation_ = rotation;
}

const Vec3& Model::scale() const {
  return scale_;
}

void Model::set_scale(const Vec3& scale) {
  scale_ = scale;
}
