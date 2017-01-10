#include "eventdata.h"
#include <tuple>

EventData::EventData()
  : EventData(0, 0)
{}

EventData::EventData(int mouse_x, int mouse_y)
  : mouse_coords_ { std::make_tuple(mouse_x, mouse_y) }
{}

const std::tuple<int,int>& EventData::mouse_coords() const {
  return mouse_coords_;
}
