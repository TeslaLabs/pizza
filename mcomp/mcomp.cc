#include "mcomp.h"
#include <cstdio>
#include <string>
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

  event_.Set("Backspace_down", [this](void* data) {
    this->event_.Call("quit", nullptr);
  });

  // event_.Set("m1_down", [this](void* data) {
  //   auto coords = static_cast<std::tuple<int,int>>(data);
  //   std::tie(x, y) = static_cast<std::tuple<int,int>>(data);
  //   std::sprintf(&message[0], "m1_down => x: %d  y: %d", x, y);
  //   log_.Message(message);
  // });

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
