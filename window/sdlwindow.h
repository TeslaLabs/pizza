#ifndef PIZZA_WINDOW_SDLWINDOW_H
#define PIZZA_WINDOW_SDLWINDOW_H

#include <functional>
#include <string>
#include <SDL2/SDL.h>
#include "iwindow.h"
#include "../log/ilog.h"

class SdlWindow : public IWindow {
  ILog& log_;
  std::string title_;
  std::function<void(int,int)> resize_func_;
  SDL_Window* window_handle_;
  SDL_GLContext glcontext_;
  unsigned int width_;
  unsigned int height_;

public:
  SdlWindow(ILog& log);
  SdlWindow(const SdlWindow& w) = delete;
  ~SdlWindow();
  std::string title() const override;
  void set_title(const std::string& title) override;
  unsigned int width() const override;
  unsigned int height() const override;
  void Resize(int width, int height) override;
  void set_resize_func(std::function<void(int,int)> resize_func) override;
  virtual void Show() override;
  virtual void Hide() override;
  virtual void ShowCursor() override;
  virtual void HideCursor() override;
  virtual void Update() override;
  SdlWindow& operator=(const SdlWindow& other) = delete;
};

#endif
