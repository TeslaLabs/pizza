#include "mcomp.h"
#include <cstdio>
#include "../event/ievent.h"
#include "../math/math.h"
#include "../render/irender.h"
#include "../window/iwindow.h"

Mcomp::Mcomp(IEvent& event,
             ILog& log,
             IRender& render,
             IWindow& window)
    : event_ { event },
      log_ { log },
      window_ { window },
      render_ { render }
{
    event_.Set("Backspace_down", [this] { this->event_.Call("quit"); });
    event_.Set("L_down", [this] { this->render_.LoadData("r"); });
    event_.Set("U_down", [this] { this->render_.UnloadData(); });

    render_.CameraPosition({ 0, 0, 1 });
    render_.CameraDirection({ 0, 0, -1 });

    auto m = Matrix::Identity();
    m.Translate(0, 0, -1);
    models_.push_back(Model { "Cube", "default" });

    window_.Show();
}

void Mcomp::Update() {
    render_.Update();
    window_.Update();
}
