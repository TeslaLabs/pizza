#ifndef TIMER_LINUXTIMER_H
#define TIMER_LINUXTIMER_H

#include "itimer.h"
#include <time.h>

class LinuxTimer : public ITimer {
  struct timespec previous_;

public:
  LinuxTimer();
  virtual void Start() override;
  virtual double dt() override;
};

#endif
