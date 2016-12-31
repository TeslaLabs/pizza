#include "mcomp.h"
#include <cstdio>
#include <sstream>
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
    event_.Set("P_down", [this] { this->render_.PrintData(); });

    render_.LoadData("r");
    models_.push_back(Model { "Cube", "basic" });

    window_.Show();
}

void Mcomp::Update() {
    for (auto& model : models_) {
        render_.DrawModel(model);
    }
    render_.Update();
    window_.Update();
}
