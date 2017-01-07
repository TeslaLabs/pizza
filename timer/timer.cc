#include "timer.h"
#include <cinttypes>

//
//                                     ,,
//         db                        `7MM
//        ;MM:                         MM
//       ,V^MM.   `7MMpdMAo.`7MMpdMAo. MM  .gP"Ya
//      ,M  `MM     MM   `Wb  MM   `Wb MM ,M'   Yb
//      AbmmmqMA    MM    M8  MM    M8 MM 8M""""""
//     A'     VML   MM   ,AP  MM   ,AP MM YM.    ,
//   .AMA.   .AMMA. MMbmmd'   MMbmmd'.JMML.`Mbmmd'
//                  MM        MM
//                .JMML.    .JMML.

#ifdef __APPLE__

#include <mach/mach.h>
#include <mach/mach_time.h>

mach_timebase_info_data_t time_info;

Timer::Timer()
  : prev_time_ { mach_absolute_time() }
{
  mach_timebase_info(&time_info);
}

double Timer::dt() {
  uint64_t curtime, elapsed_absolute, elapsed_nano;
  curtime = mach_absolute_time();
  elapsed_absolute = curtime - prev_time_;
  elapsed_nano = (elapsed_absolute / time_info.denom) * time_info.numer;
  double dt = static_cast<double>(elapsed_nano) / 1e9;
  prev_time_ = curtime;
  return dt;
}

#endif

//
//                 ,,
//   `7MMF'        db
//     MM
//     MM        `7MM  `7MMpMMMb.`7MM  `7MM  `7M'   `MF'
//     MM          MM    MM    MM  MM    MM    `VA ,V'
//     MM      ,   MM    MM    MM  MM    MM      XMX
//     MM     ,M   MM    MM    MM  MM    MM    ,V' VA.
//   .JMMmmmmMMM .JMML..JMML  JMML.`Mbod"YML..AM.   .MA.
//
//

#ifdef __linux__

#include <time.h>

static struct timespec previous;

Timer::Timer()
  : prev_time_ { 0 }
{
  clock_gettime(CLOCK_MONOTONIC, &previous);
}

double Timer::dt() {
  struct timespec curtime;
  clock_gettime(CLOCK_MONOTONIC, &curtime);

  auto dsec = curtime.tv_sec - previous.tv_sec;
  auto dnano = curtime.tv_nsec - previous.tv_nsec;

  if (dnano < 0) {
    dnano += 1000000000;
    --dsec;
  }

  dnano += (dsec * 1000000000);
  double dt = static_cast<double>(dnano) / 1e9;
  previous = curtime;
  return dt;
}

#endif
