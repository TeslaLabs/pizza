#ifndef TIMER_ITIMER_H
#define TIMER_ITIMER_H

class ITimer {
public:
  virtual void Start() = 0;
  virtual double dt() = 0;
};

#endif
