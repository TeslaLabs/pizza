#include "engine.h"
#include <cstdio>
#include <cstdlib>
#include "igame.h"
#include "../event/ievent.h"
#include "../log/ilog.h"
#include "../timer/itimer.h"

Engine::Engine(IEvent& event,
               ILog& log,
               IGame& game,
               ITimer& timer)
  : event_ { event },
    log_ { log },
    game_ { game },
    timer_ { timer },
    alive_ { true }
{
  event_.Set("quit", [this](void* data) { this->alive_ = false; });
}

void Engine::Run() {
  while (alive_) {
    auto dt = timer_.dt();
    timer_.Start();

    event_.Process();
    game_.Update(dt);
  }
}
