#include "glrender.h"
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <debug.h>
#include <gl/gl_headers.h>
#include "../math/math.h"
#include "../math/vec3.h"
#include "../proto/data.pb.h"
#include "../window/iwindow.h"

//
//                          ,,        ,,    ,,
//   `7MM"""Mq.            *MM      `7MM    db
//     MM   `MM.            MM        MM
//     MM   ,M9 `7MM  `7MM  MM,dMMb.  MM  `7MM  ,p6"bo
//     MMmmdM9    MM    MM  MM    `Mb MM    MM 6M'  OO
//     MM         MM    MM  MM     M8 MM    MM 8M
//     MM         MM    MM  MM.   ,M9 MM    MM YM.    ,
//   .JMML.       `Mbod"YML.P^YbmdP'.JMML..JMML.YMbmd'
//
//

GLRender::GLRender(ILog& log, IWindow& window)
	: log_ { log },
    window_ { window },
	  assets_loaded_ { false }
{
}

GLRender::~GLRender() {
  UnloadData();
}

bool GLRender::Initialize() {
#ifndef __APPLE__
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    log_.Error("Could not initialize GLEW");
  }

  bool is_valid { true };
#endif

  std::unordered_set<std::string> extensions;
  const unsigned char* ext_str { glGetString(GL_EXTENSIONS) };
  auto ext = std::strtok((char*) ext_str, " ");
  if (ext) extensions.insert(ext);
  while ((ext = std::strtok(nullptr, " "))) extensions.insert(ext);

#define lm(m) log_.Message(m)
#define EXTCHECK(ext) { \
    std::string xt_str { ext }; \
    auto xt = extensions.find(xt_str); \
    if (xt != extensions.end()) lm(xt_str + ": YES"); \
    else lm(xt_str + ": NO"); \
  }

  EXTCHECK("GL_ARB_shader_objects")
  EXTCHECK("GL_ARB_vertex_shader")
  EXTCHECK("GL_ARB_fragment_shader")

#undef lm
#undef EXTCHECK

  glClearColor(0.5, 0.0, 0.0, 1.0);
  glEnable(GL_DEPTH_TEST); ErrorCheck("enable depth testing");
  glEnable(GL_CULL_FACE); ErrorCheck("enable cull face");
  glFrontFace(GL_CCW); ErrorCheck("set front face");
  glCullFace(GL_BACK); ErrorCheck("set to cull back faces");

  return true;
}

std::function<void(int,int)> GLRender::GetResizeFunction() {
  return [](int width, int height) {
    glViewport(0, 0, width, height);
  };
}

void GLRender::Update() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  ErrorCheck("glclear");

  RenderModels(CalculateViewMatrix());

  window_.Update();
}

void GLRender::LoadData(const std::string& filepath) {
  if (assets_loaded_) UnloadData();

  std::ifstream file { filepath, std::ios::binary };
  if (!file) { log_.Error("Could not open data file"); return; }

  Data data;
  if (!data.ParseFromIstream(&file)) {
    log_.Error("Could not parse data file");
    return;
  }

  if (!ImportMeshes(data)) {
    log_.Error("Could not import meshes");
    return;
  }

  if (!ImportShaders(data)) {
    log_.Error("Could not import shaders");
    return;
  }
}

void GLRender::UnloadData() {
  if (!assets_loaded_) return;

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  glUseProgram(0);

  for (auto& m : meshes_) {
    glDeleteBuffers(1, &m.second.position_buffer);
    glDeleteBuffers(1, &m.second.index_buffer);
    glDeleteVertexArrays(1, &m.second.vao_id);
  }

  for (auto& s : shaders_) {
    s.second.ClearUniforms();
    glDeleteShader(s.second.vert_id);
    glDeleteShader(s.second.frag_id);
    glDeleteProgram(s.second.program_id);
  }

  shaders_.clear();
  meshes_.clear();
  assets_loaded_ = false;
}

void GLRender::SetBackgroundColor(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
}

const Matrix& GLRender::camera_projection() const {
  return camera_.projection;
}

void GLRender::set_camera_projection(const Matrix& projection) {
  camera_.projection = projection;
}

const Vec3& GLRender::camera_position() const {
  return camera_.position;
}

void GLRender::set_camera_position(const Vec3& position) {
  camera_.position = position;
}

const Vec3& GLRender::camera_rotation() const {
  return camera_.rotation;
}

void GLRender::set_camera_rotation(const Vec3& rotation) {
  camera_.rotation = rotation;
}

void GLRender::CameraLook(const Vec3& direction) {
  // TODO
}

void GLRender::CameraLookat(const Vec3& location) {
  // TODO
}

void GLRender::DrawModel(IModel* model) {
  models_.push_back(model);
}

//
//                           ,,
//     `7MM"""Mq.            db                    mm
//       MM   `MM.                                 MM
//       MM   ,M9 `7Mb,od8 `7MM `7M'   `MF',6"Yb.mmMMmm .gP"Ya
//       MMmmdM9    MM' "'   MM   VA   ,V 8)   MM  MM  ,M'   Yb
//       MM         MM       MM    VA ,V   ,pm9MM  MM  8M""""""
//       MM         MM       MM     VVV   8M   MM  MM  YM.    ,
//     .JMML.     .JMML.   .JMML.    W    `Moo9^Yo.`Mbmo`Mbmmd'
//
//

void GLRender::ErrorCheck(const std::string& message) {
  DEBUG({
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
      std::string error_message;
      switch (err) {
        case GL_INVALID_ENUM: {
          error_message = message + " [Invalid enum]";
        } break;
        case GL_INVALID_VALUE: {
          error_message = message + " [Invalid value]";
        } break;
        case GL_INVALID_OPERATION: {
          error_message = message + " [Invalid operation]";
        } break;
        case GL_OUT_OF_MEMORY: {
          error_message = message + " [Out of memory]";
        } break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: {
          error_message = message + " [Invalid framebuffer operation]";
        } break;
        default: {
          std::stringstream format;
          format << message << " [" << std::hex << err << "]";
          error_message = format.str();
        }
      }
      log_.Error(error_message);
    }
  })
}

void GLRender::AddPrimitives() {
  const float positions[] {
     1.0,  1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    -1.0,  1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    -1.0, -1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
     1.0, -1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0
  };
  const unsigned int indices[] {
    0, 1, 2,
    2, 3, 0
  };

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint bufs[2];
  glGenBuffers(2, bufs);

  glBindBuffer(GL_ARRAY_BUFFER, bufs[0]);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(float) * 8 * 4,
               positions,
               GL_STATIC_DRAW);

  glVertexAttribPointer(static_cast<unsigned int>(AttribLoc::Position),
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(float) * 8,
                        nullptr);
  glVertexAttribPointer(static_cast<unsigned int>(AttribLoc::Normal),
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(float) * 8,
                        (GLvoid*) (sizeof(float) * 3));
  glVertexAttribPointer(static_cast<unsigned int>(AttribLoc::Uv),
                        2,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(float) * 8,
                        (GLvoid*) (sizeof(float) * 6));
  glEnableVertexAttribArray(static_cast<unsigned int>(AttribLoc::Position));
  glEnableVertexAttribArray(static_cast<unsigned int>(AttribLoc::Normal));
  glEnableVertexAttribArray(static_cast<unsigned int>(AttribLoc::Uv));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufs[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(unsigned int) * 3 * 2,
               indices,
               GL_STATIC_DRAW);

  meshes_["plane"].position_buffer = bufs[0];
  meshes_["plane"].index_buffer = bufs[1];
  meshes_["plane"].vao_id = vao;
  meshes_["plane"].n_faces = 6;

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

bool GLRender::ImportMeshes(const Data& data) {
  AddPrimitives();
  for (auto i = 0; i < data.mesh_size(); ++i) {
    auto mesh = data.mesh(i);

    auto mesh_result = meshes_.find(mesh.name());
    if (mesh_result != meshes_.end()) {
      log_.Error(mesh.name() + " already exists!");
      continue;
    }

    GLuint vao_id { 0 };
    glGenVertexArrays(1, &vao_id); ErrorCheck("gen vertex arrays");
    glBindVertexArray(vao_id); ErrorCheck("bind vertex array");

    GLuint position_buffer { 0 }, index_buffer { 0 };
    glGenBuffers(1, &position_buffer); ErrorCheck("gen position buffer");

    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    ErrorCheck("bind array buffer");

    auto n_positions = 8 * mesh.vertex_size();
    auto positions = new float[n_positions];

    for (auto j = 0; j < mesh.vertex_size(); ++j) {
      positions[(j * 8) + 0] = mesh.vertex(j).x();
      positions[(j * 8) + 1] = mesh.vertex(j).y();
      positions[(j * 8) + 2] = mesh.vertex(j).z();
      positions[(j * 8) + 3] = mesh.vertex(j).i();
      positions[(j * 8) + 4] = mesh.vertex(j).j();
      positions[(j * 8) + 5] = mesh.vertex(j).k();
      positions[(j * 8) + 6] = mesh.vertex(j).u();
      positions[(j * 8) + 7] = mesh.vertex(j).v();
    }

    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(float) * n_positions,
                 positions,
                 GL_STATIC_DRAW);
    ErrorCheck("array buffer data");

    glVertexAttribPointer(static_cast<unsigned int>(AttribLoc::Position),
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(float) * 8,
                          nullptr);
    ErrorCheck("position attrib pointer");
    glVertexAttribPointer(static_cast<unsigned int>(AttribLoc::Normal),
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(float) * 8,
                          (GLvoid*) (sizeof(float) * 3));
    ErrorCheck("normal attrib pointer");
    glVertexAttribPointer(static_cast<unsigned int>(AttribLoc::Uv),
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(float) * 8,
                          (GLvoid*) (sizeof(float) * 6));
    ErrorCheck("uv attrib pointer");

    glEnableVertexAttribArray(static_cast<unsigned int>(AttribLoc::Position));
    ErrorCheck("enable position attrib array");
    glEnableVertexAttribArray(static_cast<unsigned int>(AttribLoc::Normal));
    ErrorCheck("enable normal attrib array");
    glEnableVertexAttribArray(static_cast<unsigned int>(AttribLoc::Uv));
    ErrorCheck("enable uv attrib array");

    glGenBuffers(1, &index_buffer); ErrorCheck("gen index buffer");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    ErrorCheck("bind element buffer");

    auto n_faces = 3 * mesh.face_size();
    auto faces = new unsigned int[n_faces];

    for (auto j = 0; j < mesh.face_size(); ++j) {
      faces[(j * 3) + 0] = mesh.face(j).a();
      faces[(j * 3) + 1] = mesh.face(j).b();
      faces[(j * 3) + 2] = mesh.face(j).c();
    }

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(unsigned int) * n_faces,
                 faces,
                 GL_STATIC_DRAW);
    ErrorCheck("element buffer data");

    meshes_[mesh.name()].position_buffer = position_buffer;
    meshes_[mesh.name()].index_buffer = index_buffer;
    meshes_[mesh.name()].vao_id = vao_id;
    meshes_[mesh.name()].n_faces = n_faces;

    delete[] positions;
    delete[] faces;

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  return true;
}

bool GLRender::ImportShaders(const Data& data) {
  struct ShaderData {
    std::string vert_source;
    std::string frag_source;
  };

  std::unordered_map<std::string, ShaderData> shaders;

  for (auto i = 0; i < data.shader_size(); ++i) {
    if (data.shader(i).type() == "fragment") {
      auto name = data.shader(i).name();
      auto source = data.shader(i).source();
      shaders[name].frag_source = source;
    }
    if (data.shader(i).type() == "vertex") {
      auto name = data.shader(i).name();
      auto source = data.shader(i).source();
      shaders[name].vert_source = source;
    }
  }

  for (auto& shader : shaders) {
    DEBUG(log_.Message("Processing shader, \"" + shader.first + "\""));
    auto shader_result = shaders_.find(shader.first);
    if (shader_result != shaders_.end()) {
      log_.Error(shader.first + " already exists!");
      continue;
    }

    if (shader.second.vert_source == "" ||
        shader.second.frag_source == "") {
      std::stringstream error_message;
      error_message << "Do not have both vertex and fragment shaders for ";
      error_message << "shader, \"" << shader.first << "\"";
      log_.Error(error_message.str());
    }

    GLuint vert_id, frag_id;
    if (!CompileShader(shader.second.vert_source, kVertex, &vert_id)) {
      log_.Error("Could not compile vertex shader");
      continue;
    }

    if (!CompileShader(shader.second.frag_source, kFragment, &frag_id)) {
      log_.Error("Could not compile fragment shader");
      glDeleteShader(vert_id);
      continue;
    }

    GLuint program_id;
    if (!CreateShaderProgram(vert_id, frag_id, &program_id)) {
      log_.Error("Could not create shader");
      glDeleteShader(vert_id);
      glDeleteShader(frag_id);
      continue;
    }

    shaders_[shader.first].vert_id = vert_id;
    shaders_[shader.first].frag_id = frag_id;
    shaders_[shader.first].program_id = program_id;

    ProcessUniforms(shaders_[shader.first]);
  }

  return true;
}

bool GLRender::CompileShader(const std::string& source,
                             ShaderType type,
                             GLuint* out_shader) {
  GLuint shader;
  std::string type_str;
  switch (type) {
    case kVertex: {
      shader = glCreateShader(GL_VERTEX_SHADER);
      type_str = "vertex shader";
    } break;
    case kFragment: {
      shader = glCreateShader(GL_FRAGMENT_SHADER);
      type_str = "fragment shader";
    } break;
    default: return false;
  }
  ErrorCheck("shader creation");

  auto source_c_str = source.c_str();
  glShaderSource(shader, 1, &source_c_str, nullptr);
  ErrorCheck("shader source");
  glCompileShader(shader);
  ErrorCheck("compile shader");

  DEBUG({
    GLint log_size;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
    if (log_size > 2) {
      std::string error_log;
      error_log.reserve(log_size);
      glGetShaderInfoLog(shader, log_size, &log_size, &error_log[0]);
      log_.Error(type_str + " log:");
      log_.Error("--- START ---");
      log_.Error(error_log);
      log_.Error("---  END  ---");
    }
  })

  GLint success { GL_FALSE };
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (success != GL_TRUE) {
    glDeleteShader(shader);
    return false;
  }

  *out_shader = shader;
  DEBUG(log_.Message("Successfully compiled " + type_str));

  return true;
}

bool GLRender::CreateShaderProgram(GLuint vert_id,
                                   GLuint frag_id,
                                   GLuint* out_id) {
  GLuint shader = glCreateProgram();
  ErrorCheck("create shader");
  if (!shader) {
    log_.Error("Could not create shader");
    return false;
  }

  glAttachShader(shader, vert_id); ErrorCheck("attach vert shader");
  glAttachShader(shader, frag_id); ErrorCheck("attach frag shader");

  glBindAttribLocation(shader, static_cast<unsigned int>(AttribLoc::Position), "in_position");
  ErrorCheck("bind in_position attrib location");
  glBindAttribLocation(shader, static_cast<unsigned int>(AttribLoc::Normal), "in_normal");
  ErrorCheck("bind in_normal attrib location");
  glBindAttribLocation(shader, static_cast<unsigned int>(AttribLoc::Uv), "in_uv");
  ErrorCheck("bind in_uv attrib location");

  if (!LinkShaderProgram(shader)) {
    log_.Error("Could not link shader");
    glDetachShader(shader, vert_id);
    glDetachShader(shader, frag_id);
    glDeleteProgram(shader);
    return false;
  }

  *out_id = shader;
  DEBUG(log_.Message("Successfully compiled shader"));
  return true;
}

bool GLRender::LinkShaderProgram(GLuint program_id) {
  glLinkProgram(program_id);
  ErrorCheck("link shader");

  DEBUG({
    GLint log_size;
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_size);
    if (log_size > 2) {
      std::string error_message;
      error_message.reserve(log_size);
      glGetProgramInfoLog(program_id,
                          log_size,
                          &log_size,
                          &error_message[0]);
      log_.Error("Shader linking");
      log_.Error(error_message);
    }
  })

  GLint success { GL_FALSE };
  glGetProgramiv(program_id, GL_LINK_STATUS, &success);
  if (success != GL_TRUE) {
    log_.Error("Could not link shader");
    return false;
  }
  return true;
}

// The goal is to parse the shaders individually and pull out the uniforms
// names from them, but for now they will be hardcoded
void GLRender::ProcessUniforms(Shader& shader) {
  auto projection_location = glGetUniformLocation(shader.program_id,
                                                  "projection");
  ErrorCheck("get projection location");
  if (projection_location != -1) {
    shader.SetUniformLocation("projection", projection_location);

    auto modelview_location = glGetUniformLocation(shader.program_id,
                                                   "modelview");
    if (modelview_location != -1) {
      shader.SetUniformLocation("modelview", modelview_location);
    }
  }
}

Matrix GLRender::CalculateViewMatrix() {
  auto view = Matrix::Identity();
  view = (Matrix::RotateX(-camera_.rotation.i()) *
          Matrix::RotateY(-camera_.rotation.j()));
  view = view * Matrix::Translate(-camera_.position.i(),
                                  -camera_.position.j(),
                                  -camera_.position.k());
  return view;
}

void GLRender::RenderModels(const Matrix& view) {
  for (auto model : models_) {
    auto mesh_result = meshes_.find(model->name());
    if (mesh_result == meshes_.end()) {
      std::stringstream message;
      message << "Could not find mesh, \"" << model->name() << "\"";
      log_.Error(message.str());
      return;
    }

    auto shader_result = shaders_.find(model->shader_name());
    if (shader_result == shaders_.end()) {
      std::stringstream message;
      message << "Could not find shader, \"" << model->shader_name();
      message << "\" to render mesh";
      log_.Error(message.str());
      return;
    }

    glUseProgram(shader_result->second.program_id);

    auto& mesh_info = mesh_result->second;
    glBindVertexArray(mesh_info.vao_id);

    auto& shader = shader_result->second;
    shader.SetUniformValue("projection",
                           [this](GLint location) {
                            glUniformMatrix4fv(location,
                                               1,
                                               GL_FALSE,
                                               this->camera_.projection.data());
                            this->ErrorCheck("projection matrix");
                           });
    auto model_translate = Matrix::Translate(model->position().i(),
                                             model->position().j(),
                                             model->position().k());
    auto model_rotate = (Matrix::RotateX(model->rotation().i()) *
                         Matrix::RotateY(model->rotation().j()) *
                         Matrix::RotateZ(model->rotation().k()));
    auto model_matrix = model_translate * model_rotate;
    auto modelview = view * model_matrix;
    shader.SetUniformValue("modelview",
                           [&modelview, this](GLint location) {
                            glUniformMatrix4fv(location,
                                               1,
                                               GL_FALSE,
                                               modelview.data());
                            this->ErrorCheck("modelview matrix");
                           });
    glDrawElements(GL_TRIANGLES,
                   mesh_info.n_faces,
                   GL_UNSIGNED_INT,
                   nullptr);
    ErrorCheck("draw elements");
  }
  models_.clear();
}
