#ifndef EVENT_IEVENT_H
#define EVENT_IEVENT_H

#include <functional>
#include <string>

class IEvent {
public:
  virtual void Process() = 0;
  virtual void Set(const std::string& event,
                   std::function<void(void*)> command) = 0;
  virtual void Remove(const std::string& event) = 0;
  virtual void Call(const std::string& event, void* data) = 0;
};

#endif
