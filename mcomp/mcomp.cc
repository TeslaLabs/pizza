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
  window_.set_width(960);
  window_.set_height(540);

  event_.Set("Backspace_down", [this] { this->event_.Call("quit"); });

  event_.Set("L", [this] {
    auto pos = this->models_[0].position();
    pos.set_i(pos.i() + 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("J", [this] {
    auto pos = this->models_[0].position();
    pos.set_i(pos.i() - 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("I", [this] {
    auto pos = this->models_[0].position();
    pos.set_j(pos.j() + 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("K", [this] {
    auto pos = this->models_[0].position();
    pos.set_j(pos.j() - 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("U", [this] {
    auto pos = this->models_[0].position();
    pos.set_k(pos.k() + 10 * this->dt_);
    this->models_[0].set_position(pos);
  });
  event_.Set("O", [this] {
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

void Mcomp::Update(double dt) {
  dt_ = dt;

  for (auto m : models_) {
    render_.DrawModel(&m);
  }

  render_.Update();
}
