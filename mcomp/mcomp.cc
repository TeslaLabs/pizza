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
    camera_sensitivity_ { .15 },
    mouse_sensitivity_ { .5 },
    prev_mouse_x_ { -1 },
    prev_mouse_y_ { -1 }
{
  window_.set_title("mcomp");

  MainMode();

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

//
//                                                         ,,
//     .g8"""bgd                    mm                   `7MM
//   .dP'     `M                    MM                     MM
//   dM'       ` ,pW"Wq.`7MMpMMMb.mmMMmm `7Mb,od8 ,pW"Wq.  MM  ,pP"Ybd
//   MM         6W'   `Wb MM    MM  MM     MM' "'6W'   `Wb MM  8I   `"
//   MM.        8M     M8 MM    MM  MM     MM    8M     M8 MM  `YMMMa.
//   `Mb.     ,'YA.   ,A9 MM    MM  MM     MM    YA.   ,A9 MM  L.   I8
//     `"bmmmd'  `Ybmd9'.JMML  JMML.`Mbmo.JMML.   `Ybmd9'.JMML.M9mmmP'
//
//

void Mcomp::MainMode() {
  event_.Set("Backspace_down", [this](const EventData& ed) {
    QuitMode();
  });
  event_.Set("m1_down", [this](const EventData& ed) {
    ToRotateMode(ed);
  });
  event_.Set("m1_up", [this](const EventData& ed) {
    FromRotateMode();
  });
  event_.Set("Space_down", [this](const EventData& ed) {
    ToFlyMode(ed);
  });
  event_.Set("Space_up", [this](const EventData& ed) {
    FromFlyMode();
  });
}

void Mcomp::QuitMode() {
  event_.Call("quit", EventData());
}

void Mcomp::ToRotateMode(const EventData& ed) {
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
}

void Mcomp::FromRotateMode() {
  event_.Remove("mmove");
}

void Mcomp::ToFlyMode(const EventData& ed) {
  window_.SetCursorPosition(window_.width() / 2, window_.height() / 2);
  window_.HideCursor();
  event_.Set("mmove", [this](const EventData& ed) {
    auto x = std::get<0>(ed.mouse_coords());
    auto y = std::get<1>(ed.mouse_coords());

    int dx { x - static_cast<int>(window_.width() / 2) };
    int dy { y - static_cast<int>(window_.height() / 2) };

    auto rotation = render_.camera_rotation();
    float di { rotation.i() - dy * camera_sensitivity_ };
    float dj { rotation.j() - dx * camera_sensitivity_ };
    dj += dj < 0.0 ? 360.0 : dj > 360.0 ? -360.0 : 0.0;
    rotation.set_i(di > 90.0 ? 90.0 : di < -90.0 ? -90 : di);
    rotation.set_j(dj);
    render_.set_camera_rotation(rotation);

    window_.SetCursorPosition(window_.width() / 2, window_.height() / 2);
  });
}

void Mcomp::FromFlyMode() {
  window_.ShowCursor();
  event_.Remove("mmove");
}
