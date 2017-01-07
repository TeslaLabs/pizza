#ifndef WINDOW_WINDOW_H
#define WINDOW_WINDOW_H

#include <functional>
#include <string>
#include "../render/irender.h"

class IWindow {
public:
  virtual std::string title() const = 0;
  virtual void set_title(const std::string& title) = 0;
  virtual unsigned int width() const = 0;
  virtual void set_width(int width) = 0;
  virtual unsigned int height() const = 0;
  virtual void set_height(int height) = 0;
  virtual void set_resize_func(std::function<void(int,int)> resize_func) = 0;
  virtual void Show() = 0;
  virtual void Hide() = 0;
  virtual void Update() = 0;
};

#endif
