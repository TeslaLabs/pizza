#include "engine.h"
#include <cstdio>
#include <cstdlib>
#include "igame.h"
#include "../event/ievent.h"
#include "../log/ilog.h"

Engine::Engine(IEvent& event,
               ILog& log,
               IGame& game)
    : event_ { event },
      log_ { log },
      game_ { game },
      alive_ { true }
{
    event_.Set("quit", [this] { this->alive_ = false; });
}

void Engine::Run() {
    while (alive_) {
        event_.Process();
        game_.Update();
    }
}
