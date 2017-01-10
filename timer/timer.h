#ifndef TIMER_TIMER_H
#define TIMER_TIMER_H

#ifdef __APPLE__
  #include "appletimer.h"
  class Timer : public AppleTimer {};
#elif __linux__
  #include "linuxtimer.h"
  class Timer : public LinuxTimer {};
#endif

#endif
