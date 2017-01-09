#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "igame.h"
#include "../event/ievent.h"
#include "../log/ilog.h"
#include "../timer/itimer.h"

class Engine {
  IEvent& event_;
  ILog& log_;
  IGame& game_;
  ITimer& timer_;
  bool alive_;
  int max_fps_;

public:
  Engine(IEvent& event, ILog& log, IGame& game, ITimer& timer);
  void set_max_fps(int max_fps);
  void Run();
};

#endif
