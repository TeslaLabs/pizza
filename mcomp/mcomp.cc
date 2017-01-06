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
    window_ { window }
{
  window_.set_title("mcomp");
  window_.set_width(960);
  window_.set_height(540);

  event_.Set("Backspace_down", [this] { this->event_.Call("quit"); });
  event_.Set("A_down", [this] {
    this->models_.clear();
    this->models_.push_back(Model { "Thing", "default" });
  });
  event_.Set("B_down", [this] {
    this->models_.clear();
    this->models_.push_back(Model { "Sphere", "default" });
  });

  render_.LoadData("r");
  render_.SetCameraProjection(Matrix::Projection(ToRadians(70),
                                                 4.0 / 3.0,
                                                 1.0,
                                                 10000.0));
  render_.SetCameraPosition({ 0, 0, 500 });
  models_.push_back(Model { "Thing", "default" });

  window_.Show();
}

void Mcomp::Update(double dt) {
  std::string fps;
  fps.reserve(32);
  std::sprintf(&fps[0], "%4.1f", 1.0 / dt);
  log_.Message(fps);

  for (auto m : models_) {
    render_.DrawModel(&m);
  }

  render_.Update();
}
