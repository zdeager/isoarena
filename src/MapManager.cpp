#include "MapManager.h"

#include <fstream>

#include "Engine.h"

MapManager::MapManager() {}

MapManager::~MapManager() {}

bool MapManager::loadFromFile(std::string name, std::string tilesetFile,
                              int tilesetWidth, int tilesetHeight,
                              int tileWidth, int tileHeight,
                              std::string mapFile, int mapWidth, int mapHeight,
                              int mapTileWidth, int mapTileHeight)
{
  Map *map = new Map(name);
  map->setTileset(name, tilesetFile, tilesetWidth, tilesetHeight, tileWidth,
                  tileHeight);
  map->setMap(mapFile, mapWidth, mapHeight, mapTileWidth, mapTileHeight);
  // Add Map to Map map
  mMapMap.insert(std::pair<std::string, Map *>(name, map));

  // TODO: this should actually check for success
  return true;
}

Map *MapManager::getMap(std::string name) { return mMapMap[name]; }

// Returns Texture from texture map
void MapManager::unloadAll()
{
  // Iterate over texture map and destroy Textures
  std::map<std::string, Map *>::iterator itr;
  for (itr = mMapMap.begin(); itr != mMapMap.end(); itr++) delete itr->second;
  // Clear texture map
  mMapMap.clear();
}

Map::Map(std::string name)
{
  mClips = NULL;
  mTiles = NULL;
  mName = name;
}

Map::~Map()
{
  // Deallocate Tiles
  for (int i = 0; i < mNumTiles; ++i)
  {
    if (mTiles[i])
    {
      delete mTiles[i];
      mTiles[i] = NULL;
    }
  }
  if (mTiles) delete[] mTiles;

  // Dealloc clips
  if (mClips) delete[] mClips;
}

bool Map::setTileset(std::string name, std::string file, int tileSetWidth,
                     int tileSetHeight, int tileWidth, int tileHeight)
{
  // Loading success flag
  bool textureLoaded = true;

  // Helper variables
  int i, j, idx;

  // Load tileset texture
  TextureManager::get().loadFromFile(name, file);

  // Set tile/tileset params
  mTileSetWidth = tileSetWidth;
  mTileSetHeight = tileSetHeight;
  mTileWidth = tileWidth;
  mTileHeight = tileHeight;

  // Alloc tileset clips
  mClips = new SDL_Rect[mTileSetWidth * mTileSetHeight];

  // Clip the tileset sheet
  for (i = 0; i < mTileSetHeight; i++)
  {
    for (j = 0; j < mTileSetWidth; j++)
    {
      idx = (i * mTileSetWidth) + j;
      mClips[idx].x = j * mTileWidth;
      mClips[idx].y = i * mTileHeight;
      mClips[idx].w = mTileWidth;
      mClips[idx].h = mTileHeight;
    }
  }

  return textureLoaded;
}

bool Map::setMap(std::string file, int mapWidth, int mapHeight,
                 int mapTileWidth, int mapTileHeight)
{
  // Set map dimensions
  mMapWidth = mapWidth;
  mMapHeight = mapHeight;
  mMapWidthPx = mMapWidth * mTileWidth;
  mMapHeightPx = mMapHeight * mTileHeight;

  // Set map tile dimensions
  mMapTileWidth = mapTileWidth;
  mMapTileHeight = mapTileHeight;

  // Total number of tiles in map
  mNumTiles = mMapWidth * mMapHeight;

  // Alloc Tile array
  mTiles = new Tile *[mNumTiles];

  // Success flag
  bool tilesLoaded = true;

  // Helper variables
  int i, j, tileType;

  // Open the map
  std::ifstream mapFile(file);
  // If the map couldn't be loaded
  if (mapFile.fail())
  {
    printf("Unable to load map file!\n");
    tilesLoaded = false;
  }
  else
  {
    for (i = 0; i < mMapHeight; i++)
    {
      for (j = 0; j < mMapWidth; j++)
      {
        // Determines what kind of tile will be made
        tileType = -1;

        // Read tile from map file
        mapFile >> tileType;

        // If the was a problem in reading the map
        if (mapFile.fail())
        {
          // Stop loading map
          printf("Error loading map: Unexpected end of file!\n");
          tilesLoaded = false;
          break;
        }

        // If the number is a valid tile number
        if ((tileType >= -1) && (tileType < (mTileSetWidth * mTileSetHeight)))
        {
          mTiles[i * mMapWidth + j] =
              new Tile(j, i, mTileWidth, mTileHeight, mMapTileWidth,
                       mMapTileHeight, tileType, &mClips[tileType], true);
        }
        // If we don't recognize the tile type
        else
        {
          printf("Error loading map: Invalid tile type at %d, %d -> NULL\n", i,
                 j);
          mTiles[i * mMapWidth + j] = NULL;
        }
      }
    }
    // Close the file
    mapFile.close();
  }

  // If the map/tileset was loaded fine
  return tilesLoaded;
}

void Map::render()
{
  for (int i = 0; i < mNumTiles; ++i)
    if (mTiles[i])
      mTiles[i]->render(TextureManager::get().getTexture(mName),
                        Engine::get().getCamera());
}

int Map::getWidthPx() { return mMapWidthPx; }

int Map::getHeightPx() { return mMapHeightPx; }

Tile::Tile(int x, int y, int w, int h, int mapw, int maph, int type,
           SDL_Rect *clip, bool walkable)
{
  // Set map coords
  mX = x;
  mY = y;

  // Set world coords (transformed)
  mBox.x = (x - y) * (mapw / 2);
  mBox.y = (x + y) * (maph / 2);

  // Set tile dimensions
  mBox.w = w;
  mBox.h = h;

  // Set tile type
  mType = type;

  // Set tileset clip
  mClip = clip;

  // Set walkability
  mWalkable = walkable;
}

void Tile::render(Texture *texture, SDL_Rect *camera)
{
  // If the tile is on screen -> render tile
  if (SDL_HasIntersection(camera, &mBox))
    texture->render(mBox.x - camera->x, mBox.y - camera->y, mClip);
}

bool Tile::getWalkable() { return mWalkable; }