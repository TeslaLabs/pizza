#ifndef ENGINE_IGAME_H
#define ENGINE_IGAME_H

class IGame {
public:
  virtual void Update(double dt) = 0;
};

#endif
