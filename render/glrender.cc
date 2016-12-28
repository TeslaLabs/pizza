#include "glrender.h"
#include <cstdio>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <debug.h>
#include <gl/gl_headers.h>
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
}

GLRender::~GLRender() {
    UnloadData();
}

void GLRender::Update() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

    for (auto& m : meshes_) {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glDeleteBuffers(1, &m.second.position_buffer);
        glDeleteBuffers(1, &m.second.index_buffer);
        glDeleteVertexArrays(1, &m.second.vao);
    }

    for (auto& p : shaders_) {
        glUseProgram(0);

        p.second.ClearUniforms();
        glDeleteShader(p.second.vert_id);
        glDeleteShader(p.second.frag_id);
        glDeleteShader(p.second.shader_id);
    }

    shaders_.clear();
    meshes_.clear();
    assets_loaded_ = false;
}

// void GLRender::SetUniformMatrices(const std::string& program,
//                                   const std::string& uniform,
//                                   int n_matrices,
//                                   Matrix* matrices) {
//     auto program_result = programs_.find(program);
//     if (program_result == programs_.end()) {
//         std::stringstream message;
//         message << "Could not find program, \"" << program;
//         message << ",\" to set uniform, \"" << uniform << "\"";
//         log_.Error(message.str());
//         return;
//     }

//     constexpr unsigned int MAX_MATRICES = 64;
//     float data[MAX_MATRICES * 16];
//     for (auto i = 0; i < MAX_MATRICES && i < n_matrices; ++i) {
//         data[(i * 16) + 0] = matrices[i][0];
//         data[(i * 16) + 1] = matrices[i][1];
//         data[(i * 16) + 2] = matrices[i][2];
//         data[(i * 16) + 3] = matrices[i][3];
//         data[(i * 16) + 4] = matrices[i][4];
//         data[(i * 16) + 5] = matrices[i][5];
//         data[(i * 16) + 6] = matrices[i][6];
//         data[(i * 16) + 7] = matrices[i][7];
//         data[(i * 16) + 8] = matrices[i][8];
//         data[(i * 16) + 9] = matrices[i][9];
//         data[(i * 16) + 10] = matrices[i][10];
//         data[(i * 16) + 11] = matrices[i][11];
//         data[(i * 16) + 12] = matrices[i][12];
//         data[(i * 16) + 13] = matrices[i][13];
//         data[(i * 16) + 14] = matrices[i][14];
//         data[(i * 16) + 15] = matrices[i][15];
//     }

//     auto set_function = [matrices, n_matrices, data] (GLint uniform_location) {
//         glUniformMatrix4fv(uniform_location,
//                            n_matrices,
//                            GL_FALSE,
//                            data);
//     };
//     if (!program_result->second.SetUniformValue(uniform, set_function)) {
//         std::stringstream message;
//         message << "Could not set uniform, \"" << uniform << "\"";
//         log_.Error(message.str());
//         return;
//     }
// }

void GLRender::CameraPosition(const Vec3& position) {
    camera_.position = position;
}

void GLRender::CameraDirection(const Vec3& direction) {
    camera_.direction = direction;
}

void GLRender::CameraLookat(const Vec3& location) {
    camera_.direction = camera_.position - location;
}

void GLRender::DrawModel(const IModel& model) {
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
        message << ",\" to render mesh";
        log_.Error(message.str());
        return;
    }
    glUseProgram(shader_result->second.shader_id);

    auto& model_info = mesh_result->second;
    glBindBuffer(GL_ARRAY_BUFFER, model_info.position_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model_info.index_buffer);
    glBindVertexArray(model_info.vao);

    auto& shader = shader_result->second;
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

bool GLRender::ImportMeshes(const Data& data) {
    for (auto i = 0; i < data.mesh_size(); ++i) {
        auto mesh = data.mesh(i);

        GLuint position_buffer;
        glGenBuffers(1, &position_buffer);
        ErrorCheck("Gen position buffer");

        glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
        ErrorCheck("Bind position buffer");

        auto positions = new float[mesh.vertex_size() * 8];
        for (auto j = 0; j < mesh.vertex_size(); j += 8) {
            positions[j + 0] = mesh.vertex(j).x();
            positions[j + 1] = mesh.vertex(j).y();
            positions[j + 2] = mesh.vertex(j).z();
            positions[j + 3] = mesh.vertex(j).i();
            positions[j + 4] = mesh.vertex(j).j();
            positions[j + 5] = mesh.vertex(j).k();
            positions[j + 6] = mesh.vertex(j).u();
            positions[j + 7] = mesh.vertex(j).v();
        }
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(float) * 8 * mesh.vertex_size(),
                     positions,
                     GL_STATIC_DRAW);
        ErrorCheck("Position buffer data");
        delete[] positions;

        GLuint index_buffer;
        glGenBuffers(1, &index_buffer);
        ErrorCheck("Gen index buffer");

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        ErrorCheck("Bind index buffer");

        auto indices = new unsigned int[mesh.face_size() * 3];
        for (auto j = 0; j < mesh.face_size(); j += 3) {
            indices[j + 0] = mesh.face(j).a();
            indices[j + 1] = mesh.face(j).b();
            indices[j + 2] = mesh.face(j).c();
        }
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     sizeof(unsigned int) * 3 * mesh.face_size(),
                     indices,
                     GL_STATIC_DRAW);
        delete[] indices;

        auto vao = GenerateVertexArrayObject();

        auto mesh_result = meshes_.find(mesh.name());
        if (mesh_result != meshes_.end()) {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            glDeleteBuffers(1, &mesh_result->second.position_buffer);
            glDeleteBuffers(1, &mesh_result->second.index_buffer);
            glDeleteVertexArrays(1, &mesh_result->second.vao);
        }
        meshes_[mesh.name()].position_buffer = position_buffer;
        meshes_[mesh.name()].index_buffer = index_buffer;
        meshes_[mesh.name()].vao = vao;
        meshes_[mesh.name()].n_faces = mesh.face_size() * 3;
    }

    return true;
}

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
        if (shader.second.vert_source == "" ||
            shader.second.frag_source == "") {
            std::stringstream err_msg;
            err_msg << "Do not have both vertex and fragment shaders for "
                    << "shader, \"" << shader.first << "\"" << std::endl;
                    log_.Error(err_msg.str());
            continue;
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
            log_.Error("Could not create shader shader");
            glDeleteShader(vert_id);
            glDeleteShader(frag_id);
            continue;
        }

        auto shader_result = shaders_.find(shader.first);
        if (shader_result != shaders_.end()) {
            glUseProgram(0);

            glDeleteShader(shader_result->second.vert_id);
            glDeleteShader(shader_result->second.frag_id);
            glDeleteProgram(shader_result->second.shader_id);
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

    GLint success { 0 };
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        DEBUG({
            std::string error_log;
            GLint log_size;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
            error_log.reserve(log_size);
            glGetShaderInfoLog(shader, log_size, &log_size, &error_log[0]);
            log_.Error(type_str);
            log_.Error(error_log);
        })
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

    GLint success = 0;
    glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
        DEBUG({
            std::string error_message;
            GLint length = 0;
            glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &length);
            error_message.reserve(length);
            glGetProgramInfoLog(shader_id,
                                length,
                                &length,
                                &error_message[0]);
            log_.Error("Shader shader");
            log_.Error(error_message.c_str());
        })
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
