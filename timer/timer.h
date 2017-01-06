#ifndef TIMER_TIMER_H
#define TIMER_TIMER_H

#include <cinttypes>

class Timer {
  uint64_t prev_time_;

public:
  Timer();
  double dt();
};

#endif
