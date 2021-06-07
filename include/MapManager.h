#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <map>
#include <string>

#include "SDL.h"
#include "TextureManager.h"

// Forward declarations
class Map;
class Tile;

class MapManager
{
  public:
  // Return singleton of texture manager
  static MapManager &get()
  {
    static MapManager manager;
    return manager;
  }
  MapManager(MapManager const &) = delete;      // Disable copy constructor
  void operator=(MapManager const &) = delete;  // Disable load operator

  // Loads map from specified files
  bool loadFromFile(std::string name, std::string tilesetFile, int tilesetWidth,
                    int tilesetHeight, int tileWidth, int tileHeight,
                    std::string mapFile, int mapWidth, int mapHeight,
                    int mapTileWidth, int mapTileHeight);

  // Return Map by name
  Map *getMap(std::string name);

  // Unload all maps (Destroy Maps)
  void unloadAll();

  private:
  // Constructor (private becuase singleton)
  MapManager();
  // Destructor (private becuase singleton)
  ~MapManager();

  // Map "friendly" map name -> Map object
  std::map<std::string, Map *> mMapMap;
};

class Map
{
  public:
  // Initializes the variables
  Map(std::string name);

  // Deallocs memory
  ~Map();

  // Set tile set texture
  bool setTileset(std::string name, std::string file, int tileSetWidth,
                  int tileSetHeight, int tileWidth, int tileHeight);

  // Parse/build tile map
  bool setMap(std::string file, int mapWidth, int mapHeight, int mapTileWidth,
              int mapTileHeight);

  // Render map
  void render();

  // Get map width/height (in pixels)
  int getWidthPx();
  int getHeightPx();

  private:
  // Map name
  std::string mName;

  // Tile set width/height (in tiles)
  int mTileSetWidth;
  int mTileSetHeight;

  // Tile width/height (in pixels)
  int mTileWidth;
  int mTileHeight;

  // Clipped tiles
  SDL_Rect *mClips;

  // Map width/height (in tiles)
  int mMapWidth;
  int mMapHeight;

  // Map TILE width/height (in pixels)
  int mMapTileWidth;
  int mMapTileHeight;

  // Map width/height (in pixels)
  int mMapWidthPx;
  int mMapHeightPx;

  // Number of tiles in map
  int mNumTiles;

  // The actual Tiles making up the map
  Tile **mTiles;
};

class Tile
{
  public:
  // Initializes tile
  Tile(int x, int y, int w, int h, int mapw, int maph, int type, SDL_Rect *clip,
       bool walkable);

  // Shows the tile
  void render(Texture *texture, SDL_Rect *camera);

  // Get walkabililty
  bool getWalkable();

  private:
  // The tile coords (map coords)
  int mX, mY;

  // The tile rect (for rendering)
  SDL_Rect mBox;

  // The tile type (from tileset)
  int mType;

  // Clip from tileset
  SDL_Rect *mClip;

  // Tile walkability (based on map)
  bool mWalkable;
};

#endif