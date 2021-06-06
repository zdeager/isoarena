#ifndef STATEINTRO_H
#define STATEINTRO_H

#include "SDL.h"
#include "State.h"

class StateIntro : public State
{
  public:
  // Return singleton of Intro State
  static StateIntro &get()
  {
    static StateIntro intro;
    return intro;
  }
  StateIntro(StateIntro const &) = delete;      // Disable copy constructor
  void operator=(StateIntro const &) = delete;  // Disable load operator

  void init();
  void cleanup();

  void pause();
  void resume();

  void handleEvents();
  void update();
  void render();

  private:
  StateIntro();
  ~StateIntro();
};

#endif