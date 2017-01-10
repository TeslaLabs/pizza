#ifndef EVENT_EVENTDATA_H
#define EVENT_EVENTDATA_H

#include <tuple>

class EventData {
  std::tuple<int,int> mouse_coords_;

public:
  EventData();
  EventData(int mouse_x, int mouse_y);
  const std::tuple<int,int>& mouse_coords() const;
};

#endif
