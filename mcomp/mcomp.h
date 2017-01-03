#ifndef MCOMP_MCOMP_H
#define MCOMP_MCOMP_H

#include <vector>
#include "../engine/igame.h"
#include "../event/ievent.h"
#include "../log/ilog.h"
#include "../render/irender.h"
#include "../render/model.h"
#include "../window/iwindow.h"

class Mcomp : public IGame {
  IEvent& event_;
  ILog& log_;
  IRender& render_;
  IWindow& window_;
  std::vector<Model> models_;

public:
  Mcomp(IEvent& event,
        ILog& log,
        IRender& render,
        IWindow& window);
  virtual void Update() override;
};

#endif
