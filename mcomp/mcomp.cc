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
    dt_ { 0 }
{
  window_.set_title("mcomp");
  window_.Resize(960, 540);

  event_.Set("Backspace_down", [this](void* data) {
    this->event_.Call("quit", nullptr);
  });

  event_.Set("m1_down", [this](void* data) {
    event_.Set("mmove", [this](void* data) {
      if (data == nullptr) return;
      auto coords = *static_cast<std::tuple<int,int>*>(data);
      auto x = std::get<0>(coords);
      auto y = std::get<1>(coords);
      // std::string message;
      // message.reserve(128);
      char message[128];
      std::sprintf(message, "x: %d  y: %d", x, y);
      log_.Message(message);
    });
  });
  event.Set("m1_up", [this](void* data) {
    this->event_.Remove("mmove");
  });

  event_.Set("L", [this](void* data) {
    auto pos = this->models_[0].position();
    pos.set_i(pos.i() + 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("J", [this](void* data) {
    auto pos = this->models_[0].position();
    pos.set_i(pos.i() - 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("I", [this](void* data) {
    auto pos = this->models_[0].position();
    pos.set_j(pos.j() + 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("K", [this](void* data) {
    auto pos = this->models_[0].position();
    pos.set_j(pos.j() - 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("U", [this](void* data) {
    auto pos = this->models_[0].position();
    pos.set_k(pos.k() + 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("O", [this](void* data) {
    auto pos = this->models_[0].position();
    pos.set_k(pos.k() - 10 * this->dt_);
    this->models_[0].set_position(pos);
  });

  render_.LoadData("r");
  render_.SetCameraProjection(Matrix::Projection(90,
                                                 16.0 / 9.0,
                                                 1.0,
                                                 1000000.0));
  render_.SetCameraPosition({ 0, 0, 10 });
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
