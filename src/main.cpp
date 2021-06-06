#include "Engine.h"
#include "StateIntro.h"

extern "C"
{
#include "lua/lauxlib.h"
#include "lua/lua.h"
#include "lua/lualib.h"
}

int main(__attribute__((unused)) int argc, __attribute__((unused)) char *args[])
{
  // Test lua stuff
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  luaL_dofile(L, "script.lua");

  // Create/initialize engine
  Engine::get().init();

  // Load assets
  Engine::get().loadAssets();

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