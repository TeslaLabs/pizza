#include "engine.h"
#include <cstdio>
#include <cstdlib>
#include "igame.h"
#include "../event/eventdata.h"
#include "../event/ievent.h"
#include "../log/ilog.h"
#include "../timer/itimer.h"

Engine::Engine(IEvent& event, ILog& log, IGame& game, ITimer& timer)
  : event_ { event },
    log_ { log },
    game_ { game },
    timer_ { timer },
    alive_ { true },
    max_fps_ { 120 }
{
  event_.Set("quit", [this](const EventData& data) { this->alive_ = false; });
}

void Engine::set_max_fps(int max_fps) {
  max_fps_ = max_fps;
}

void Engine::Run() {
  while (alive_) {
    auto dt = timer_.dt();
    if (dt < 1.0 / max_fps_) continue;
    timer_.Start();

    event_.Process();
    game_.Update(dt);
  }
}
