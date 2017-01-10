#include "appletimer.h"
#include <cinttypes>
#include <mach/mach.h>
#include <mach/mach_time.h>

AppleTimer::AppleTimer() {
  mach_timebase_info(&time_info_);
}

void AppleTimer::Start() {
  previous_ = mach_absolute_time();
}

double AppleTimer::dt() {
  uint64_t curtime, elapsed_absolute, elapsed_nano;
  curtime = mach_absolute_time();
  elapsed_absolute = curtime - previous_;
  elapsed_nano = (elapsed_absolute / time_info_.denom) * time_info_.numer;
  double dt = static_cast<double>(elapsed_nano) / 1e9;
  return dt;
}
