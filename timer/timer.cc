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
  double dt = (double) elapsed_nano / 1e9;
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
