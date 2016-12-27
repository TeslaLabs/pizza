#ifndef RENDER_IRENDER_H
#define RENDER_IRENDER_H

#include <string>
#include "imodel.h"
#include "../math/vec3.h"

class IRender {
public:
    virtual ~IRender() = 0;
    virtual void Update() = 0;
    virtual void LoadData(const std::string& filepath) = 0;
    virtual void UnloadData() = 0;
    virtual void CameraPosition(const Vec3& position) = 0;
    virtual void CameraDirection(const Vec3& location) = 0;
    virtual void CameraLookat(const Vec3& location) = 0;
    virtual void DrawModel(const IModel& model) = 0;
};

#endif
