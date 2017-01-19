#ifndef RENDER_GLRENDER_H
#define RENDER_GLRENDER_H

#include <functional>
#include <gl/gl_headers.h>
#include <string>
#include <unordered_map>
#include "imodel.h"
#include "irender.h"
#include "../log/ilog.h"
#include "../math/matrix.h"
#include "../math/vec3.h"
#include "../proto/data.pb.h"
#include "../window/iwindow.h"

class GLRender : public IRender {
  enum ShaderType {
    kVertex,
    kFragment
  };
  enum {
    ATTRIB_LOC_POSITION = 0,
    ATTRIB_LOC_NORMAL = 1,
    ATTRIB_LOC_UV = 2
  };

  struct Shader {
    GLuint vert_id;
    GLuint frag_id;
    GLuint program_id;
    Shader();
    Shader(const Shader& s) = delete;
    void ClearUniforms();
    void SetUniformLocation(const std::string& uniform,
                            GLint uniform_location);
    bool SetUniformValue(const std::string& uniform,
                         std::function<void(GLint)> SetValue);
  private:
    std::unordered_map<std::string, GLint> uniforms_;
  };

  struct Camera {
    Matrix projection;
    Vec3 position;
    Vec3 rotation;
    Camera();
  };

  struct Mesh {
    GLuint position_buffer;
    GLuint index_buffer;
    GLuint vao_id;
    unsigned int n_faces;
    Mesh();
    Mesh(const Mesh& m) = delete;
  };

  ILog& log_;
  IWindow& window_;
  Camera camera_;
  std::unordered_map<std::string, Shader> shaders_;
  std::unordered_map<std::string, Mesh> meshes_;
  std::vector<IModel*> models_;
  bool assets_loaded_;

public:
  GLRender(ILog& log, IWindow& window);
  virtual ~GLRender() override;
  virtual bool Initialize() override;
  virtual std::function<void(int,int)> GetResizeFunction() override;
  virtual void Update() override;
  virtual void LoadData(const std::string& filepath) override;
  virtual void UnloadData() override;
  virtual void SetBackgroundColor(float r, float g, float b, float a) override;
  virtual const Matrix& camera_projection() const override;
  virtual void set_camera_projection(const Matrix& projection) override;
  virtual const Vec3& camera_position() const override;
  virtual void set_camera_position(const Vec3& position) override;
  virtual const Vec3& camera_rotation() const override;
  virtual void set_camera_rotation(const Vec3& rotation) override;
  virtual void CameraLook(const Vec3& direction) override;
  virtual void CameraLookat(const Vec3& location) override;
  virtual void DrawModel(IModel* model) override;

private:
  void ErrorCheck(const std::string& message);
  void AddPrimitives();
  bool ImportMeshes(const Data& data);
  bool ImportShaders(const Data& data);
  bool CompileShader(const std::string& source,
                     ShaderType type,
                     GLuint* out);
  bool CreateShaderProgram(GLuint vert_id,
                           GLuint frag_id,
                           GLuint* out_id);
  bool LinkShaderProgram(GLuint shader_id);
  void ProcessUniforms(Shader& shader);
  Matrix CalculateViewMatrix();
  void RenderModels(const Matrix& view);
};

#endif
