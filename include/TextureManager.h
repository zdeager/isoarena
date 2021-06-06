#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <string>

#include "SDL.h"

// Forward declaration
class Texture;

class TextureManager
{
  public:
  // Return singleton of texture manager
  static TextureManager &get()
  {
    static TextureManager manager;
    return manager;
  }
  TextureManager(TextureManager const &) = delete;  // Disable copy constructor
  void operator=(TextureManager const &) = delete;  // Disable load operator

  // Loads image at specified path
  bool loadFromFile(std::string name, std::string path, bool key = false,
                    uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0);

  // Returns Texture from texture map
  Texture *getTexture(std::string name);

  private:
  // Constructor (private becuase singleton)
  TextureManager();
  // Destructor (private becuase singleton)
  ~TextureManager();

  // Map "friendly" texture name -> texture object
  std::map<std::string, Texture *> mTextureMap;
};

class Texture
{
  public:
  // Initializes variables
  Texture(SDL_Texture *texture, int width, int height);

  // Deallocates memory
  ~Texture();

  // Deallocates texture
  void free();

  // Set color modulation
  void setColor(uint8_t red, uint8_t green, uint8_t blue);

  // Set blending
  void setBlendMode(SDL_BlendMode blending);

  // Set alpha modulation
  void setAlpha(uint8_t alpha);

  // Renders texture at given point
  void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0,
              SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

  private:
  // The actual hardware texture
  SDL_Texture *mTexture;

  // Image dimensions
  int mWidth;
  int mHeight;
};

#endif