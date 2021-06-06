
#include "StateIntro.h"

#include <stdio.h>

#include "Engine.h"
#include "SDL.h"
#include "State.h"
#include "StatePlay.h"

StateIntro::StateIntro() {}

StateIntro::~StateIntro() {}

void StateIntro::init()
{
  // Load dummy image
  SDL_Surface* loadedSurface = IMG_Load("res/intro.png");
  // Create texture from surface pixels
  mIntro =
      SDL_CreateTextureFromSurface(Engine::get().getRenderer(), loadedSurface);
  // Get rid of old loaded surface
  SDL_FreeSurface(loadedSurface);

  printf("StateIntro Init\n");
}

void StateIntro::cleanup()
{
  // Deallocate surface
  SDL_DestroyTexture(mIntro);
  mIntro = NULL;

  printf("StateIntro Cleanup\n");
}

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
  SDL_RenderCopy(Engine::get().getRenderer(), mIntro, NULL, NULL);

  // Update screen
  SDL_RenderPresent(Engine::get().getRenderer());
}
