#include "sdlevent.h"
#include <cstdio>
#include <sstream>
#include <string>
#include <unordered_map>
#include <SDL2/SDL.h>
#include "eventdata.h"
#include "../log/ilog.h"

//
//                            ,,        ,,    ,,
//     `7MM"""Mq.            *MM      `7MM    db
//       MM   `MM.            MM        MM
//       MM   ,M9 `7MM  `7MM  MM,dMMb.  MM  `7MM  ,p6"bo
//       MMmmdM9    MM    MM  MM    `Mb MM    MM 6M'  OO
//       MM         MM    MM  MM     M8 MM    MM 8M
//       MM         MM    MM  MM.   ,M9 MM    MM YM.    ,
//     .JMML.       `Mbod"YML.P^YbmdP'.JMML..JMML.YMbmd'
//
//

SdlEvent::SdlEvent(ILog& log)
  : log_ { log }
{}

void SdlEvent::Process() {
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_KEYDOWN: {
        int x, y;
        SDL_GetMouseState(&x, &y);
        KeyDown(std::string { SDL_GetKeyName(e.key.keysym.sym) },
                EventData(x, y));
      } break;

      case SDL_KEYUP: {
        int x, y;
        SDL_GetMouseState(&x, &y);
        KeyUp(std::string { SDL_GetKeyName(e.key.keysym.sym) },
              EventData(x, y));
      } break;

      case SDL_MOUSEBUTTONDOWN: {
        EventData data { e.button.x, e.button.y };
        switch (e.button.button) {
          case SDL_BUTTON_LEFT: {
            KeyDown("m1", data);
          } break;
          case SDL_BUTTON_RIGHT: {
            KeyDown("m2", data);
          } break;
          case SDL_BUTTON_MIDDLE: {
            KeyDown("m3", data);
          } break;
        }
      } break;

      case SDL_MOUSEBUTTONUP: {
        EventData data { e.button.x, e.button.y };
        switch (e.button.button) {
          case SDL_BUTTON_LEFT: {
            KeyUp("m1", data);
          } break;
          case SDL_BUTTON_RIGHT: {
            KeyUp("m2", data);
          } break;
          case SDL_BUTTON_MIDDLE: {
            KeyUp("m3", data);
          } break;
        }
      }

      case SDL_MOUSEMOTION: {
        EventData data { e.motion.x, e.motion.y };
        Call("mmove", data);
      } break;

      case SDL_WINDOWEVENT: {
        switch (e.window.event) {
          case SDL_WINDOWEVENT_CLOSE: {
            Call("quit", EventData());
          } break;
          case SDL_WINDOWEVENT_FOCUS_GAINED: {
            Call("window_unfocus", EventData());
          } break;
          case SDL_WINDOWEVENT_FOCUS_LOST: {
            Call("window_focus", EventData());
          } break;
        }
      } break;

      default: break;
    }
  }

  CheckActiveKeys();
}

void SdlEvent::Set(const std::string& event,
                   std::function<void(const EventData&)> command) {
  events_[event] = command;
}

void SdlEvent::Remove(const std::string& event) {
  auto event_result = events_.find(event);
  if (event_result == events_.end()) {
    std::stringstream message;
    message << "Could not find event, \"" << event << "\" for removal";
    log_.Error(message.str());
    return;
  }
  events_.erase(event_result);
}

void SdlEvent::Call(const std::string& event, const EventData& data) {
  auto func = events_.find(event);
  if (func != events_.end()) {
    func->second(data);
  }
}

//
//                           ,,
//     `7MM"""Mq.            db                    mm
//       MM   `MM.                                 MM
//       MM   ,M9 `7Mb,od8 `7MM `7M'   `MF',6"Yb.mmMMmm .gP"Ya
//       MMmmdM9    MM' "'   MM   VA   ,V 8)   MM  MM  ,M'   Yb
//       MM         MM       MM    VA ,V   ,pm9MM  MM  8M""""""
//       MM         MM       MM     VVV   8M   MM  MM  YM.    ,
//     .JMML.     .JMML.   .JMML.    W    `Moo9^Yo.`Mbmo`Mbmmd'
//
//

void SdlEvent::KeyDown(const std::string& key, const EventData& data) {
  if (!keymap_[key]) {
    keymap_[key] = true;
    Call(key + "_down", data);
  }
}

void SdlEvent::KeyUp(const std::string& key, const EventData& data) {
  if (keymap_[key]) {
    keymap_[key] = false;
    Call(key + "_up", data);
  }
}

void SdlEvent::CheckActiveKeys() {
  for (auto& key : keymap_) {
    if (key.second) Call(key.first, EventData());
  }
}
