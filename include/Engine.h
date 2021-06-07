#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

#include "SDL.h"
#include "SDL_image.h"

// Forward declartion of State
class State;

class Engine
{
  public:
  // Return singleton of engine
  static Engine &get()
  {
    static Engine engine;
    return engine;
  }
  Engine(Engine const &) = delete;          // Disable copy constructor
  void operator=(Engine const &) = delete;  // Disable load operator

  // Initialize SDL, camera, etc.
  bool init(const char *windowName = "IsoArena", int windowWidth = 640,
            int windowHeight = 480);
  // Clean up SDL
  void quit();

  // Load game assets
  bool loadAssets();
  // Unload game assets
  void unloadAssets();

  // Change state
  void changeState(State *state);
  // Push new state to stack
  void pushState(State *state);
  // Pop top state off stack
  void popState();

  // Handle input
  void handleEvents();
  // Update game data
  void update();
  // Render game data
  void render();

  // Return whether engine is still running or not
  bool isRunning() { return mIsRunning; }

  // Signal to shutdown engine (set engine running to false)
  void signalShutdown() { mIsRunning = false; }

  // Return the window
  SDL_Window *getWindow() { return mWindow; }

  // Return the renderer
  SDL_Renderer *getRenderer() { return mRenderer; }

  // Return the camera
  SDL_Rect *getCamera() { return &mCamera; }

  // Return the camera zoom
  float getCameraZoom() { return mCameraZoom; }

  private:
  // Constructor (private becuase singleton)
  Engine();
  // Destructor (private becuase singleton)
  ~Engine();

  // Whether engine is still running or not
  bool mIsRunning;

  // The stack of states
  std::vector<State *> states;

  // Window data
  SDL_Window *mWindow;
  int mWindowWidth, mWindowHeight;

  // Renderer
  SDL_Renderer *mRenderer;

  // Camera data
  SDL_Rect mCamera;
  float mCameraZoom;
};

#endif
