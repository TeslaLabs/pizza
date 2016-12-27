#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include "igame.h"
#include "../event/ievent.h"
#include "../log/ilog.h"

class Engine {
    IGame& game_;
    IEvent& event_;
    ILog& log_;
    bool alive_;

public:
    Engine(IEvent& event, ILog& log, IGame& game);
    void Run();
};

#endif