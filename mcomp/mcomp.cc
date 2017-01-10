#include "mcomp.h"
#include <cstdio>
#include <string>
#include <tuple>
#include "../event/ievent.h"
#include "../math/math.h"
#include "../render/irender.h"
#include "../window/iwindow.h"

Mcomp::Mcomp(IEvent& event, ILog& log, IRender& render, IWindow& window)
  : event_ { event },
    log_ { log },
    render_ { render },
    window_ { window },
    dt_ { 0 },
    camera_sensitivity_ { 1 },
    mouse_sensitivity_ { 1 },
    prev_mouse_x_ { -1 },
    prev_mouse_y_ { -1 }
{
  window_.set_title("mcomp");

  event_.Set("Backspace_down", [this](void* data) {
    this->event_.Call("quit", nullptr);
  });

  event_.Set("m3_down", [this](void* data) {
    this->window_.SetCursorPosition(this->window_.width() / 2,
                                    this->window_.height() / 2);
    window_.HideCursor();
    event_.Set("mmove", [this](void* data) {
      if (data == nullptr) return;

      auto coords = *static_cast<std::tuple<int,int>*>(data);
      auto x = std::get<0>(coords);
      auto y = std::get<1>(coords);

      int dx { x - static_cast<int>(this->window_.width() / 2) };
      int dy { y - static_cast<int>(this->window_.height() / 2) };

      auto rotation = this->render_.camera_rotation();
      float di { rotation.i() - dy * this->camera_sensitivity_ };
      float dj { rotation.j() - dx * this->camera_sensitivity_ };
      // rotation.set_i(di > 90.0 ? di < -90.0 ? -90.0 : 90.0 : di);
      rotation.set_i(di);
      rotation.set_j(dj);
      this->render_.set_camera_rotation(rotation);

      this->window_.SetCursorPosition(this->window_.width() / 2,
                                      this->window_.height() / 2);

    });
  });

  event_.Set("m3_up", [this](void* data) {
    window_.ShowCursor();
    event_.Remove("mmove");
  });

  event_.Set("m1_down", [this](void* data) {
    if (data == nullptr) return;

    auto coords = *static_cast<std::tuple<int,int>*>(data);
    prev_mouse_x_ = std::get<0>(coords);
    prev_mouse_y_ = std::get<1>(coords);

    event_.Set("mmove", [this](void* data) {
      if (data == nullptr) return;

      auto coords = *static_cast<std::tuple<int,int>*>(data);
      auto x = std::get<0>(coords);
      auto y = std::get<1>(coords);

      auto dx = x - prev_mouse_x_;
      auto dy = y - prev_mouse_y_;

      auto x_angle = (dy * mouse_sensitivity_) + models_[0].rotation().i();
      auto y_angle = (dx * mouse_sensitivity_) + models_[0].rotation().j();
      auto z_angle = models_[0].rotation().k();

      models_[0].set_rotation({
        static_cast<float>(x_angle),
        static_cast<float>(y_angle),
        z_angle
      });

      prev_mouse_x_ = x;
      prev_mouse_y_ = y;
    });
  });
  event_.Set("m1_up", [this](void* data) {
    this->event_.Remove("mmove");
  });

  event_.Set("D", [this](void* data) {
    auto pos = this->models_[0].position();
    pos.set_i(pos.i() + 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("A", [this](void* data) {
    auto pos = this->models_[0].position();
    pos.set_i(pos.i() - 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("W", [this](void* data) {
    auto pos = this->models_[0].position();
    pos.set_j(pos.j() + 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("S", [this](void* data) {
    auto pos = this->models_[0].position();
    pos.set_j(pos.j() - 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("Q", [this](void* data) {
    auto pos = this->models_[0].position();
    pos.set_k(pos.k() + 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("E", [this](void* data) {
    auto pos = this->models_[0].position();
    pos.set_k(pos.k() - 10 * this->dt_);
    this->models_[0].set_position(pos);
  });

  render_.LoadData("r");
  render_.set_camera_position({ 0, 0, 5 });
  Model model { "Thing", "default" };
  models_.push_back(model);

  window_.Show();
}

Mcomp::~Mcomp() {
  window_.ShowCursor();
}

void Mcomp::Update(double dt) {
  dt_ = dt;

  for (auto m : models_) {
    render_.DrawModel(&m);
  }

  render_.Update();
}
