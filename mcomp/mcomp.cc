#include "mcomp.h"
#include <cstdio>
#include <sstream>
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
  event_.Set("Backspace_down", [this] { this->event_.Call("quit"); });
  event_.Set("P_down", [this] { this->render_.PrintData(); });

  render_.LoadData("r");

  window_.Show();
}

void Mcomp::Update() {
  render_.Update();
  window_.Update();
}
