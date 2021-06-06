#ifndef STATEPLAY_H
#define STATEPLAY_H

#include "SDL.h"
#include "State.h"

class StatePlay : public State
{
  public:
  // Return singleton of Play State
  static StatePlay &get()
  {
    static StatePlay play;
    return play;
  }
  StatePlay(StatePlay const &) = delete;       // Disable copy constructor
  void operator=(StatePlay const &) = delete;  // Disable load operator

  void init();
  void cleanup();

  void pause();
  void resume();

  void handleEvents();
  void update();
  void render();

  private:
  StatePlay();
  ~StatePlay();
};

#endif