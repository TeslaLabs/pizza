#ifndef RENDER_GLRENDER_H
#define RENDER_GLRENDER_H

#include <functional>
#include <string>
#include <unordered_map>
#include <gl/gl_headers.h>
#include "imodel.h"
#include "irender.h"
#include "../log/ilog.h"
#include "../math/matrix.h"
#include "../proto/data.pb.h"

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
        GLint GetUniformLocation(const std::string& uniform) const;
        bool SetUniformValue(const std::string& uniform,
                             std::function<void(GLint)> uniform_func);
    private:
        std::unordered_map<std::string, GLint> uniforms_;
    };

    struct Camera {
        Vec3 position;
        Vec3 direction;
    };

    struct Mesh {
        GLuint position_buffer;
        GLuint index_buffer;
        GLuint vao;
        unsigned int n_faces;
        Mesh();
        Mesh(const Mesh& m) = delete;
    };

    ILog& log_;
    Camera camera_;
    std::unordered_map<std::string, Shader> programs_;
    std::unordered_map<std::string, Mesh> meshes_;
    bool assets_loaded_;


public:
    GLRender(ILog&);
    virtual ~GLRender() override;
    virtual void Update() override;
    virtual void LoadData(const std::string& filepath) override;
    virtual void UnloadData() override;
    virtual void CameraPosition(const Vec3& position) override;
    virtual void CameraDirection(const Vec3& location) override;
    virtual void CameraLookat(const Vec3& location) override;
    virtual void DrawModel(const IModel& model) override;

private:
    void ErrorCheck(const std::string& message);
    bool ImportMeshes(const Data& data);
    GLuint GenerateVertexArrayObject();
    bool ImportShaders(const Data& data);
    bool CompileShader(const std::string& source,
                       ShaderType type,
                       GLuint* out);
    bool CreateProgram(GLuint vert_shader,
                       GLuint frag_shader,
                       GLuint* out_program);
    bool LinkProgram(GLuint program_id);
    void ProcessUniforms(Shader& program);
};

#endif
