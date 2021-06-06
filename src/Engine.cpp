#include "Engine.h"

#include "State.h"
#include "TextureManager.h"

Engine::Engine() {}

Engine::~Engine()
{
  // Clear out pointers
  mWindow = NULL;
  mRenderer = NULL;
}

bool Engine::init(const char* windowName, int windowWidth, int windowHeight)
{
  // Initialization flag
  bool success = true;

  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  }
  else
  {
    // Disable texture filtering (keep pixelation)
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
    {
      printf("Warning: Linear texture filtering enabled!");
    }

    // Create window
    mWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, windowWidth,
                               windowHeight, SDL_WINDOW_SHOWN);
    if (mWindow == NULL)
    {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    }
    else
    {
      // Set window width/height
      mWindowWidth = windowWidth;
      mWindowHeight = windowHeight;
      // Create renderer for window (w/ VSYNC)
      // TODO: Use FPS not VSYNC
      mRenderer = SDL_CreateRenderer(
          mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (mRenderer == NULL)
      {
        printf("Renderer could not be created! SDL Error: %s\n",
               SDL_GetError());
        success = false;
      }
      else
      {
        // Initialize renderer color
        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        // Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
          printf("SDL_image could not initialize! SDL_image Error: %s\n",
                 IMG_GetError());
          success = false;
        }
      }
    }
  }

  // Initialize camera (scaled)
  // TODO: this probably doesn't need to be here...
  mCameraZoom = 1.0;
  mCamera.x = 0;
  mCamera.y = 0;
  mCamera.w = (int)ceil(mWindowWidth / mCameraZoom);
  mCamera.w = (int)ceil(mWindowHeight / mCameraZoom);

  // Set running and return success
  return mIsRunning = success;
}

bool Engine::loadAssets()
{
  // TODO: Add lua scripting to dynamically load assets
  TextureManager::get().loadFromFile("intro", "assets/intro.png");
  TextureManager::get().loadFromFile("play", "assets/play.png");
  return true;
}

void Engine::unloadAssets()
{
  // Destroy Textures
  TextureManager::get().unloadAll();
}

void Engine::quit()
{
  // Cleanup the all states
  while (!states.empty())
  {
    states.back()->cleanup();
    states.pop_back();
  }

  // Destroy window
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);

  // Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

void Engine::changeState(State* state)
{
  // Cleanup the current state
  if (!states.empty())
  {
    states.back()->cleanup();
    states.pop_back();
  }

  // Store and init the new state
  states.push_back(state);
  states.back()->init();
}

void Engine::pushState(State* state)
{
  // Pause current state
  if (!states.empty())
  {
    states.back()->pause();
  }

  // Store and init the new state
  states.push_back(state);
  states.back()->init();
}

void Engine::popState()
{
  // Cleanup the current state
  if (!states.empty())
  {
    states.back()->cleanup();
    states.pop_back();
  }

  // Resume previous state
  if (!states.empty())
  {
    states.back()->resume();
  }
}

void Engine::handleEvents() { states.back()->handleEvents(); }

void Engine::update() { states.back()->update(); }

void Engine::render() { states.back()->render(); }