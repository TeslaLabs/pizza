#include "glrender.h"
#include <functional>
#include <string>

GLRender::Shader::Shader()
  : vert_id { 0 },
    frag_id { 0 },
    program_id { 0 }
{
  uniforms_.clear();
}

void GLRender::Shader::ClearUniforms() {
  uniforms_.clear();
}

void GLRender::Shader::SetUniformLocation(const std::string& uniform,
                                          GLint uniform_location) {
  uniforms_[uniform] = uniform_location;
}

bool GLRender::Shader::SetUniformValue(const std::string& uniform,
                                       std::function<void(GLint)> SetValue) {
  auto uniform_search = uniforms_.find(uniform);
  if (uniform_search == uniforms_.end()) return false;

  SetValue(uniform_search->second);
  return true;
}
