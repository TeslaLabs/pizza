#ifndef EVENT_SDLEVENT_H
#define EVENT_SDLEVENT_H

#include <functional>
#include <string>
#include <unordered_map>
#include "eventdata.h"
#include "ievent.h"
#include "../log/ilog.h"

class SdlEvent : public IEvent {
  ILog& log_;
  std::unordered_map<std::string,
                     std::function<void(const EventData&)>> events_;
  std::unordered_map<std::string, bool> keymap_;

public:
  SdlEvent(ILog& log);
  virtual void Process() override;
  virtual void Set(const std::string& event,
                   std::function<void(const EventData&)> command) override;
  virtual void Remove(const std::string& event) override;
  virtual void Call(const std::string& event, const EventData& data) override;

private:
  void KeyUp(const std::string& key, const EventData& data);
  void KeyDown(const std::string& key, const EventData& data);
  void CheckActiveKeys();
};

#endif
