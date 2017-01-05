#ifndef PIZZA_WINDOW_SDLWINDOW_H
#define PIZZA_WINDOW_SDLWINDOW_H

#include <string>
#include <SDL2/SDL.h>
#include "iwindow.h"
#include "../log/ilog.h"

class SdlWindow : public IWindow {
  ILog& log_;
  std::string title_;
  SDL_Window* window_handle_;
  SDL_GLContext glcontext_;
  unsigned int width_;
  unsigned int height_;
  bool visible_;

public:
  SdlWindow(ILog& log);
  SdlWindow(const SdlWindow& w) = delete;
  ~SdlWindow();
  std::string title() const;
  void set_title(const std::string& title);
  unsigned int width() const override;
  void set_width(int width);
  unsigned int height() const override;
  void set_height(int height);
  virtual void Show() override;
  virtual void Hide() override;
  virtual void Update() override;
};

#endif
