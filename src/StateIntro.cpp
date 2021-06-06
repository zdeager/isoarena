#include "StateIntro.h"

#include "Engine.h"
#include "SDL.h"
#include "StatePlay.h"
#include "TextureManager.h"

StateIntro::StateIntro() {}

StateIntro::~StateIntro() {}

void StateIntro::init() { printf("StateIntro Init\n"); }

void StateIntro::cleanup() { printf("StateIntro Cleanup\n"); }

void StateIntro::pause() { printf("StateIntro Pause\n"); }

void StateIntro::resume() { printf("StateIntro Resume\n"); }

void StateIntro::handleEvents()
{
  SDL_Event event;

  if (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
    case SDL_QUIT:
      Engine::get().signalShutdown();
      break;

    case SDL_KEYDOWN:
      switch (event.key.keysym.sym)
      {
      case SDLK_SPACE:
        Engine::get().changeState(&StatePlay::get());
        break;
      case SDLK_ESCAPE:
        Engine::get().signalShutdown();
        break;
      }
      break;
    }
  }
}

void StateIntro::update() {}

void StateIntro::render()
{
  // Clear screen
  SDL_RenderClear(Engine::get().getRenderer());

  // Render texture to screen
  TextureManager::get().getTexture("intro")->render(0, 0);

  // Update screen
  SDL_RenderPresent(Engine::get().getRenderer());
}
