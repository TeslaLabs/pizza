#ifndef TIMER_APPLETIMER_H
#define TIMER_APPLETIMER_H

#include "itimer.h"
#include <cinttypes>
#include <mach/mach.h>
#include <mach/mach_time.h>

class AppleTimer : public ITimer {
  mach_timebase_info_data_t time_info_;
  uint64_t previous_;

public:
  AppleTimer();
  virtual void Start() override;
  virtual double dt() override;
};

#endif
