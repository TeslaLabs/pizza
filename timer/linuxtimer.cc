#include "linuxtimer.h"
#include <time.h>

LinuxTimer::LinuxTimer() {
  Start();
}

void LinuxTimer::Start() {
  clock_gettime(CLOCK_MONOTONIC, &previous_);
}

double LinuxTimer::dt() {
  struct timespec curtime;
  clock_gettime(CLOCK_MONOTONIC, &curtime);

  auto dsec = curtime.tv_sec - previous_.tv_sec;
  auto dnano = curtime.tv_nsec - previous_.tv_nsec;

  if (dnano < 0) {
    dnano += 1000000000;
    --dsec;
  }

  dnano += (dsec * 1000000000);
  auto dt = static_cast<double>(dnano) / 1e9;
  return dt;
}
