#include "glrender.h"
#include <cstdio>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <debug.h>
#include <gl/gl_headers.h>
#include "../math/math.h"
#include "../math/vec3.h"
#include "../proto/data.pb.h"

//
//                            ,,        ,,    ,,
//     `7MM"""Mq.            *MM      `7MM    db
//       MM   `MM.            MM        MM
//       MM   ,M9 `7MM  `7MM  MM,dMMb.  MM  `7MM  ,p6"bo
//       MMmmdM9    MM    MM  MM    `Mb MM    MM 6M'  OO
//       MM         MM    MM  MM     M8 MM    MM 8M
//       MM         MM    MM  MM.   ,M9 MM    MM YM.    ,
//     .JMML.       `Mbod"YML.P^YbmdP'.JMML..JMML.YMbmd'
//
//

GLRender::GLRender(ILog& log)
    : log_ { log },
      assets_loaded_ { false }
{
    glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST); ErrorCheck("enable depth testing");
    glEnable(GL_CULL_FACE); ErrorCheck("Enable cull face");
    glFrontFace(GL_CCW); ErrorCheck("set front face");
    glCullFace(GL_BACK); ErrorCheck("set to cull back faces");
}

GLRender::~GLRender() {
    UnloadData();
}

void GLRender::Update() {
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ErrorCheck("glclear");
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
        glDeleteVertexArrays(1, &m.second.vao);
    }

    for (auto& s : shaders_) {
        s.second.ClearUniforms();
        glDeleteShader(s.second.vert_id);
        glDeleteShader(s.second.frag_id);
        glDeleteShader(s.second.shader_id);
    }

    shaders_.clear();
    meshes_.clear();
    assets_loaded_ = false;
}

void GLRender::PrintData() {
    log_.Error("Printing data");
    for (auto& s : shaders_) {
        log_.Message(s.first);
        std::stringstream message;
        message << s.second.vert_id << std::endl;
        message << s.second.frag_id << std::endl;
        message << s.second.shader_id;
        log_.Message(message.str());
    }
}

void GLRender::SetBackgroundColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void GLRender::SetCameraProjection(const Matrix& projection) {
    camera_.projection = projection;
}

void GLRender::SetCameraPosition(const Vec3& position) {
    camera_.position = position;
}

void GLRender::SetCameraDirection(const Vec3& direction) {
    camera_.direction = Vec3::Normalize(direction);
}

void GLRender::CameraLookat(const Vec3& location) {
    camera_.direction = Vec3::Normalize(camera_.position - location);
}

void GLRender::DrawModel(const IModel& model) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    auto mesh_result = meshes_.find(model.name());
    if (mesh_result == meshes_.end()) {
        std::stringstream message;
        message << "Could not find mesh, \"" << model.name() << "\"";
        log_.Error(message.str());
        return;
    }

    auto shader_result = shaders_.find(model.shader_name());
    if (shader_result == shaders_.end()) {
        std::stringstream message;
        message << "Could not find shader, \"" << model.shader_name();
        message << "\" to render mesh";
        log_.Error(message.str());
        return;
    }
    glUseProgram(shader_result->second.shader_id);

    auto& mesh_info = mesh_result->second;
    // glBindBuffer(GL_ARRAY_BUFFER, mesh_info.position_buffer);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_info.index_buffer);
    // glBindVertexArray(mesh_info.vao);

    auto& shader = shader_result->second;
    shader.SetUniformValue("projection",
                           [this](GLint location) {
                            glUniformMatrix4fv(location,
                                               1,
                                               GL_FALSE,
                                               this->camera_.projection.data());
                            this->ErrorCheck("projection matrix");
                           });
    Matrix view = Matrix::Identity();
    // TODO: Rotations
    view = view * Matrix::Translate(camera_.position.i(),
                                    camera_.position.j(),
                                    camera_.position.k());
    auto model_translate = Matrix::Translate(model.position().i(),
                                             model.position().j(),
                                             model.position().k());
    auto model_rotate = Matrix::RotateX(model.rotation().i()) *
                        Matrix::RotateZ(model.rotation().k()) *
                        Matrix::RotateY(model.rotation().j());
    auto model_matrix = model_translate * model_rotate;
    auto modelview = model_matrix * view;
    shader.SetUniformValue("modelview",
                           [&modelview, this](GLint location) {
                            glUniformMatrix4fv(location,
                                               1,
                                               GL_FALSE,
                                               modelview.data());
                            this->ErrorCheck("modelview matrix");
                           });
    glPointSize(100.0f);
    glDrawArrays(GL_POINTS, 0, 1);
    // glDrawElements(GL_TRIANGLES,
    //                mesh_info.n_faces,
    //                GL_UNSIGNED_INT,
    //                NULL);
    ErrorCheck("draw elements");
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

GLRender::Mesh::Mesh()
    : position_buffer { 0 },
      index_buffer { 0 },
      vao { 0 },
      n_faces { 0 }
{}

GLRender::Shader::Shader()
    : vert_id { 0 },
      frag_id { 0 },
      shader_id { 0 }
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

GLRender::Camera::Camera()
    : projection {
        Matrix::Projection(ToRadians(90), 4.0 / 3.0, 1.0, 100000.0)
      },
      position { Vec3 { 0, 0, 0 } },
      direction { Vec3 { 0, 0, -1 } }
{}

void GLRender::ErrorCheck(const std::string& message) {
DEBUG(
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
                    error_message = message +
                                    " [Invalid framebuffer operation]";
                } break;
                default: {
                    std::stringstream format;
                    format << message << " [" << std::hex << err << "]";
                    error_message = format.str();
                } break;
            }
            log_.Error(error_message);
        })
}

void GLRender::AddPrimitive() {
    GLuint position_buffer, index_buffer;
}

bool GLRender::ImportMeshes(const Data& data) {
    AddPrimitive();
    for (auto i = 0; i < data.mesh_size(); ++i) {
        auto mesh = data.mesh(i);

        auto mesh_result = meshes_.find(mesh.name());
        if (mesh_result != meshes_.end()) {
            log_.Error(mesh.name() + " already exists! Skipping...");
            continue;
        }

        GLuint position_buffer, index_buffer;
        glGenBuffers(1, &position_buffer); ErrorCheck("Gen position buffer");
        glGenBuffers(1, &index_buffer); ErrorCheck("Gen index buffer");

        glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
        ErrorCheck("Bind array buffer");
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        ErrorCheck("Bind element buffer");

        auto n_positions = 8 * mesh.vertex_size();
        auto positions = new float[n_positions];
        auto n_faces = 3 * mesh.face_size();
        auto faces = new unsigned int[n_faces];

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

        for (auto j = 0; j < mesh.face_size(); ++j) {
            faces[(j * 3) + 0] = mesh.face(j).a();
            faces[(j * 3) + 1] = mesh.face(j).b();
            faces[(j * 3) + 2] = mesh.face(j).c();
        }

        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(float) * n_positions,
                     positions,
                     GL_STATIC_DRAW);
        ErrorCheck("Array buffer data");
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(unsigned int) * n_faces,
                     faces,
                     GL_STATIC_DRAW);
        ErrorCheck("Element buffer data");

        auto vao = GenerateVertexArrayObject();

        meshes_[mesh.name()].position_buffer = position_buffer;
        meshes_[mesh.name()].index_buffer = index_buffer;
        meshes_[mesh.name()].vao = vao;
        meshes_[mesh.name()].n_faces = n_faces;

        delete[] positions;
        delete[] faces;

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    return true;
}

// bool GLRender::ImportMeshes(const Data& data) {
//     for (auto i = 0; i < data.mesh_size(); ++i) {
//         auto mesh = data.mesh(i);

//         GLuint position_buffer;
//         glGenBuffers(1, &position_buffer);
//         ErrorCheck("Gen position buffer");

//         glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
//         ErrorCheck("Bind position buffer");

//         auto positions = new float[mesh.vertex_size() * 8];
//         for (auto j = 0; j < mesh.vertex_size(); ++j) {
//             positions[(j * 8) + 0] = mesh.vertex(j).x();
//             positions[(j * 8) + 1] = mesh.vertex(j).y();
//             positions[(j * 8) + 2] = mesh.vertex(j).z();
//             positions[(j * 8) + 3] = mesh.vertex(j).i();
//             positions[(j * 8) + 4] = mesh.vertex(j).j();
//             positions[(j * 8) + 5] = mesh.vertex(j).k();
//             positions[(j * 8) + 6] = mesh.vertex(j).u();
//             positions[(j * 8) + 7] = mesh.vertex(j).v();
//         }
//         glBufferData(GL_ARRAY_BUFFER,
//                      sizeof(float) * 8 * mesh.vertex_size(),
//                      positions,
//                      GL_STATIC_DRAW);
//         ErrorCheck("Position buffer data");
//         delete[] positions;

//         GLuint index_buffer;
//         glGenBuffers(1, &index_buffer);
//         ErrorCheck("Gen index buffer");

//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
//         ErrorCheck("Bind index buffer");

//         auto indices = new unsigned int[mesh.face_size() * 3];
//         for (auto j = 0; j < mesh.face_size(); ++j) {
//             indices[(j * 3) + 0] = mesh.face(j).a();
//             indices[(j * 3) + 1] = mesh.face(j).b();
//             indices[(j * 3) + 2] = mesh.face(j).c();
//         }
//         glBufferData(GL_ELEMENT_ARRAY_BUFFER,
//                      sizeof(unsigned int) * 3 * mesh.face_size(),
//                      indices,
//                      GL_STATIC_DRAW);
//         delete[] indices;

//         auto vao = GenerateVertexArrayObject();

//         auto mesh_result = meshes_.find(mesh.name());
//         if (mesh_result != meshes_.end()) {
//             glBindBuffer(GL_ARRAY_BUFFER, 0);
//             glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//             glBindVertexArray(0);

//             glDeleteBuffers(1, &mesh_result->second.position_buffer);
//             glDeleteBuffers(1, &mesh_result->second.index_buffer);
//             glDeleteVertexArrays(1, &mesh_result->second.vao);
//         }
//         meshes_[mesh.name()].position_buffer = position_buffer;
//         meshes_[mesh.name()].index_buffer = index_buffer;
//         meshes_[mesh.name()].vao = vao;
//         meshes_[mesh.name()].n_faces = mesh.face_size() * 3;
//     }

//     return true;
// }

GLuint GLRender::GenerateVertexArrayObject() {
    GLuint vao;

    glGenVertexArrays(1, &vao); ErrorCheck("Gen vertex array");
    glBindVertexArray(vao); ErrorCheck("Bind vertex array");

    glEnableVertexAttribArray(ATTRIB_LOC_POSITION);
    ErrorCheck("Enable vertex attrib array position");
    glEnableVertexAttribArray(ATTRIB_LOC_NORMAL);
    ErrorCheck("Enable vertex attrib array normal");
    glEnableVertexAttribArray(ATTRIB_LOC_UV);
    ErrorCheck("Enable vertex attrib array uv");

    glVertexAttribPointer(ATTRIB_LOC_POSITION,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(float) * 8,
                          NULL);
    ErrorCheck("Vertex attrib pointer position");
    glVertexAttribPointer(ATTRIB_LOC_NORMAL,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(float) * 8,
                          (GLvoid*) (sizeof(float) * 3));
    ErrorCheck("Vertex attrib pointer normal");
    glVertexAttribPointer(ATTRIB_LOC_UV,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(float) * 8,
                          (GLvoid*) (sizeof(float) * 6));
    ErrorCheck("Vertex attrib opinter normal");

    return vao;
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
        DEBUG(log_.Message("Processing " + shader.first));
        auto shader_result = shaders_.find(shader.first);
        if (shader_result != shaders_.end()) {
            log_.Error(shader.first + " already exists! Skipping...");
            continue;
        }

        if (shader.second.vert_source == "" ||
            shader.second.frag_source == "") {
            std::stringstream error_message;
            error_message << "Do not have both vertex and ";
            error_message << "fragment shaders for shader, \"";
            error_message << shader.first << "\"";
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

        GLuint shader_id;
        if (!CreateShader(vert_id, frag_id, &shader_id)) {
            log_.Error("Could not create shader");
            glDeleteShader(vert_id);
            glDeleteShader(frag_id);
            continue;
        }

        shaders_[shader.first].vert_id = vert_id;
        shaders_[shader.first].frag_id = frag_id;
        shaders_[shader.first].shader_id = shader_id;

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
    ErrorCheck("Shader creation");

    auto source_c_str = source.c_str();
    glShaderSource(shader, 1, &source_c_str, NULL);
    ErrorCheck("Shader source");
    glCompileShader(shader);
    ErrorCheck("Compile shader");

    DEBUG({
        GLint log_size;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
        if (log_size) {
            std::string error_log;
            error_log.reserve(log_size);
            glGetShaderInfoLog(shader, log_size, &log_size, &error_log[0]);
            log_.Error(type_str);
            log_.Error(error_log);
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

bool GLRender::CreateShader(GLuint vert_id,
                            GLuint frag_id,
                            GLuint* out_id) {
    GLuint shader = glCreateProgram();
    ErrorCheck("Create shader");
    if (!shader) {
        log_.Error("Could not create shader");
        return false;
    }

    glAttachShader(shader, vert_id); ErrorCheck("Attach vertex shader");
    glAttachShader(shader, frag_id); ErrorCheck("Attach fragment shader");

    glBindAttribLocation(shader, ATTRIB_LOC_POSITION, "in_position");
    ErrorCheck("Bind in_position attrib location");

    glBindAttribLocation(shader, ATTRIB_LOC_NORMAL, "in_normal");
    ErrorCheck("Bind in_normal attrib location");

    glBindAttribLocation(shader, ATTRIB_LOC_UV, "in_uv");
    ErrorCheck("Bind in_uv attrib location");

    if (!LinkShader(shader)) {
        log_.Error("Could not link shader shader");
        glDetachShader(shader, vert_id);
        glDetachShader(shader, frag_id);
        glDeleteProgram(shader);
        return false;
    }

    *out_id = shader;
    DEBUG(log_.Message("Successfully compiled shader"));
    return true;
}

bool GLRender::LinkShader(GLuint shader_id) {
    glLinkProgram(shader_id);
    ErrorCheck("Link shader");

    DEBUG({
        GLint log_size;
        glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &log_size);
        if (log_size) {
            std::string error_message;
            error_message.reserve(log_size);
            glGetProgramInfoLog(shader_id,
                                log_size,
                                &log_size,
                                &error_message[0]);
            log_.Error("Shader linking");
            log_.Error(error_message.c_str());
        }
    })

    GLint success = 0;
    glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
        log_.Error("Could not link shader");
        return false;
    }
    return true;
}

// The goal is to parse the shaders individually and pull out the uniforms
// names from them, but for right now they will be hardcoded
void GLRender::ProcessUniforms(Shader& shader) {
    auto projection_location = glGetUniformLocation(shader.shader_id,
                                                    "projection");
    ErrorCheck("Get projection location");
    if (projection_location != -1) {
        shader.SetUniformLocation("projection", projection_location);
    }

    auto modelview_location = glGetUniformLocation(shader.shader_id,
                                                   "modelview");
    if (modelview_location != -1) {
        shader.SetUniformLocation("modelview", modelview_location);
    }
}
