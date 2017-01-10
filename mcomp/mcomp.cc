#include "mcomp.h"
#include <cstdio>
#include <string>
#include <tuple>
#include "../event/eventdata.h"
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
    camera_sensitivity_ { .1 },
    mouse_sensitivity_ { 1 },
    prev_mouse_x_ { -1 },
    prev_mouse_y_ { -1 }
{
  window_.set_title("mcomp");

  event_.Set("Backspace_down", [this](const EventData& ed) {
    this->event_.Call("quit", EventData());
  });

  event_.Set("m3_down", [this](const EventData& ed) {
    this->window_.SetCursorPosition(this->window_.width() / 2,
                                    this->window_.height() / 2);
    window_.HideCursor();
    event_.Set("mmove", [this](const EventData& ed) {
      auto x = std::get<0>(ed.mouse_coords());
      auto y = std::get<1>(ed.mouse_coords());

      int dx { x - static_cast<int>(this->window_.width() / 2) };
      int dy { y - static_cast<int>(this->window_.height() / 2) };

      auto rotation = this->render_.camera_rotation();
      float di { rotation.i() - dy * this->camera_sensitivity_ };
      float dj { rotation.j() - dx * this->camera_sensitivity_ };
      dj += dj < 0.0 ? 360.0 : dj > 360.0 ? -360.0 : 0.0;
      rotation.set_i(di > 90.0 ? 90.0 : di < -90.0 ? -90.0 : di);
      rotation.set_j(dj);
      this->render_.set_camera_rotation(rotation);

      this->window_.SetCursorPosition(this->window_.width() / 2,
                                      this->window_.height() / 2);

    });
  });

  event_.Set("m3_up", [this](const EventData& ed) {
    window_.ShowCursor();
    event_.Remove("mmove");
  });

  event_.Set("m1_down", [this](const EventData& ed) {
    prev_mouse_x_ = std::get<0>(ed.mouse_coords());
    prev_mouse_y_ = std::get<1>(ed.mouse_coords());

    event_.Set("mmove", [this](const EventData& ed) {
      auto x = std::get<0>(ed.mouse_coords());
      auto y = std::get<1>(ed.mouse_coords());

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
  event_.Set("m1_up", [this](const EventData& ed) {
    this->event_.Remove("mmove");
  });

  event_.Set("D", [this](const EventData& ed) {
    auto pos = this->models_[0].position();
    pos.set_i(pos.i() + 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("A", [this](const EventData& ed) {
    auto pos = this->models_[0].position();
    pos.set_i(pos.i() - 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("W", [this](const EventData& ed) {
    auto pos = this->models_[0].position();
    pos.set_j(pos.j() + 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("S", [this](const EventData& ed) {
    auto pos = this->models_[0].position();
    pos.set_j(pos.j() - 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("Q", [this](const EventData& ed) {
    auto pos = this->models_[0].position();
    pos.set_k(pos.k() + 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("E", [this](const EventData& ed) {
    auto pos = this->models_[0].position();
    pos.set_k(pos.k() - 10 * this->dt_);
    this->models_[0].set_position(pos);
  });

  render_.LoadData("r");
  render_.set_camera_position({ 0, 0, 5 });
  render_.set_camera_projection(Matrix::Projection(70,
                                                   4.0 / 3.0,
                                                   1.0,
                                                   1000000.0));
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
