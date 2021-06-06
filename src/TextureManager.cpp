#include "TextureManager.h"

#include "Engine.h"
#include "SDL_image.h"

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {}

bool TextureManager::loadFromFile(std::string name, std::string path, bool key,
                                  uint8_t red, uint8_t green, uint8_t blue)
{
  // The hardware texture
  SDL_Texture *newTexture = NULL;

  // Load image at specified path
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL)
  {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
           IMG_GetError());
  }
  else
  {
    // Color key image (if necessary)
    if (key)
    {
      SDL_SetColorKey(loadedSurface, SDL_TRUE,
                      SDL_MapRGB(loadedSurface->format, red, green, blue));
    }

    // Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(Engine::get().getRenderer(),
                                              loadedSurface);
    if (newTexture == NULL)
    {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
             SDL_GetError());
    }
    else
    {
      // Create Texture
      Texture *texture =
          new Texture(newTexture, loadedSurface->w, loadedSurface->h);
      // Add Texture to texture map
      mTextureMap.insert(std::pair<std::string, Texture *>(name, texture));
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(loadedSurface);
  }

  // Return success
  return newTexture != NULL;
}

// Returns Texture from texture map
void TextureManager::unloadAll()
{
  // Iterate over texture map and destroy Textures
  std::map<std::string, Texture *>::iterator itr;
  for (itr = mTextureMap.begin(); itr != mTextureMap.end(); itr++)
    delete itr->second;
  // Clear texture map
  mTextureMap.clear();
}

// Returns Texture from texture map
Texture *TextureManager::getTexture(std::string name)
{
  // TODO: add existence check
  return mTextureMap[name];
}

Texture::Texture(SDL_Texture *texture, int width, int height)
{
  // Initialize
  mTexture = texture;
  mWidth = width;
  mHeight = height;
}

Texture::~Texture()
{
  // Free texture if it exists
  if (mTexture != NULL)
  {
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
  }
}

void Texture::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
  // Modulate texture rgb
  SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending)
{
  // Set blending function
  SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture::setAlpha(uint8_t alpha)
{
  // Modulate texture alpha
  SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Texture::render(int x, int y, SDL_Rect *clip, double angle,
                     SDL_Point *center, SDL_RendererFlip flip)
{
  // Set rendering space and render to screen
  SDL_Rect renderQuad = {x, y, mWidth, mHeight};

  // Set clip rendering dimensions
  if (clip != NULL)
  {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  // Render to screen
  SDL_RenderCopyEx(Engine::get().getRenderer(), mTexture, clip, &renderQuad,
                   angle, center, flip);
}
