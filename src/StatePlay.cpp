#include "StatePlay.h"

#include "Engine.h"
#include "SDL.h"
#include "StateIntro.h"
#include "TextureManager.h"

StatePlay::StatePlay() {}

StatePlay::~StatePlay() {}

void StatePlay::init() { printf("StatePlay Init\n"); }

void StatePlay::cleanup() { printf("StatePlay Cleanup\n"); }

void StatePlay::pause() { printf("StatePlay Pause\n"); }

void StatePlay::resume() { printf("StatePlay Resume\n"); }

void StatePlay::handleEvents()
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
      case SDLK_ESCAPE:
        Engine::get().changeState(&StateIntro::get());
        break;
      }
      break;
    }
  }
}

void StatePlay::update() {}

void StatePlay::render()
{
  // Clear screen
  SDL_RenderClear(Engine::get().getRenderer());

  // Render texture to screen
  TextureManager::get().getTexture("play")->render(0, 0);

  // Update screen
  SDL_RenderPresent(Engine::get().getRenderer());

  /*
  // Clear screen
  SDL_SetRenderDrawColor(mRenderer, 0x1E, 0x15, 0x25, 0xFF);
  SDL_RenderClear(mRenderer);

  // Scale (zoom) renderer to camera
  SDL_RenderSetScale(mRenderer, mCameraZoom, mCameraZoom);

  // Update screen
  SDL_RenderPresent(mRenderer);
  */
}
