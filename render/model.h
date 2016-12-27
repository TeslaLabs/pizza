#ifndef RENDER_MODEL_H
#define RENDER_MODEL_H

#include <string>
#include "imodel.h"
#include "../math/matrix.h"

class Model : public IModel {
    std::string name_;
    std::string shader_name_;
    Vec3 position_;
    Vec3 rotation_;
    Vec3 scale_;

public:
    Model(const std::string& name,
          const std::string& shader_name);
    virtual const std::string& name() const override;
    virtual const std::string& shader_name() const override;
    virtual const Vec3& position() const override;
    virtual void set_position(const Vec3& position) override;
    virtual const Vec3& rotation() const override;
    virtual void set_rotation(const Vec3& rotation) override;
    virtual const Vec3& scale() const override;
    virtual void set_scale(const Vec3& scale) override;
};

#endif
