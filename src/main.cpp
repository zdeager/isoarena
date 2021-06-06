#include "Engine.h"
#include "StateIntro.h"

int main(__attribute__((unused)) int argc, __attribute__((unused)) char *args[])
{
  // Create/initialize engine
  Engine::get().init();

  // Set initial state
  Engine::get().changeState(&StateIntro::get());

  // Engine loop
  while (Engine::get().isRunning())
  {
    Engine::get().handleEvents();
    Engine::get().update();
    Engine::get().render();
  }

  // Cleanup the engine
  Engine::get().quit();
  return 0;
}