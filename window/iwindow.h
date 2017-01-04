#ifndef WINDOW_WINDOW_H
#define WINDOW_WINDOW_H

class IWindow {
public:
  virtual unsigned int width() const = 0;
  virtual unsigned int height() const = 0;
  virtual void Show() = 0;
  virtual void Hide() = 0;
  virtual void Update() = 0;
};

#endif
