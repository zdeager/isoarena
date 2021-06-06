#ifndef STATE_H
#define STATE_H

#include "Engine.h"

// Abstract game state class (pure virtual functions)
class State
{
  public:
  virtual void init() = 0;
  virtual void cleanup() = 0;

  virtual void pause() = 0;
  virtual void resume() = 0;

  virtual void handleEvents() = 0;
  virtual void update() = 0;
  virtual void render() = 0;
};

#endif