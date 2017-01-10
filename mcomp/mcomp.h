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
  double dt_;
  float camera_sensitivity_;
  float mouse_sensitivity_;
  int prev_mouse_x_;
  int prev_mouse_y_;

public:
  Mcomp(IEvent& event,
        ILog& log,
        IRender& render,
        IWindow& window);
  ~Mcomp();
  virtual void Update(double dt) override;
};

#endif
