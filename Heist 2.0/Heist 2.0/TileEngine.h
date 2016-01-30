#ifndef TILEENGINE_H_INCLUDED
#define TILEENGINE_H_INCLUDED

#include "StaticEntity.h"
#include "FunctionLib.h"
#include "SFML/Graphics.hpp"

struct Tile
{
    sf::Sprite mTileSprite;
    bool mSolidState;
    float g;	//everything here and below is for A*
    float h;
    float f;
    unsigned int x;			
	unsigned int y;
    bool Closed;
    Tile* Parent;
};

class TileEngine
{
public:
    TileEngine();                               
    TileEngine(std::string pFileLocation);      //Generate from a file
	TileEngine(unsigned int pTileWidth, unsigned int pTileHeight, unsigned int pMapSizeX, unsigned int pMapSizeY, sf::Texture pTileSet, std::vector<std::vector<int> >& pTileIDVec, std::vector<std::vector<bool> >& pSolidStateVec, float pPosX = 0, float pPosY = 0);   //Generate from paramiters
	TileEngine(unsigned int pTileWidth, unsigned int pTileHeight, unsigned int pMapSizeX, unsigned int pMapSizeY, sf::Texture pTileSet, std::vector<std::vector<Tile> > pTiles, float pPosX = 0, float pPosY = 0);    //Generate from already generated Tile vector
    ~TileEngine();

    //Getters
    float GetPosX() { return mPosX; }
    float GetPosY() { return mPosY; }
    unsigned int GetTileWidth() { return mTileWidth; }
	unsigned int GetTileHeight() { return mTileHeight; }
    unsigned int GetMapSizeX() { return mMapSizeX; }
	unsigned int GetMapSizeY() { return mMapSizeY; }
    std::vector<std::vector<Tile> > GetTiles() { return mTileVec; }
	sf::Texture GetTexture() { return mTileSet; }

    //Setters
    void SetPosX(float pPosX) { mPosX = pPosX; }
    void SetPosY(float pPosY) { mPosY = pPosY; }
	void SetTileWidth(unsigned int val) { mTileWidth = val; }
	void SetTileHeight(unsigned int val) { mTileHeight = val; }
	void SetMapSizeX(unsigned int val) { mMapSizeX = val; }
	void SetMapSizeY(unsigned int val) { mMapSizeY = val; }
    void SetTiles(std::vector<std::vector<Tile> > pTiles) { mTileVec = pTiles; }
	void SetTexture(sf::Texture val) { mTileSet = val; }

    //Public member functions
    void LoadFromFile(std::string pFileLocation);
	void LoadFromParam(unsigned int tileWidth, unsigned int tileHeight, unsigned int mapSizeX, unsigned int mapSizeY, sf::Texture tileSet, std::vector<std::vector<int> >& tileIntVec, std::vector<std::vector<bool> >& tileBoolVec, float posX = 0, float posY = 0);
	void LoadFromTiles(unsigned int tileWidth, unsigned int tileHeight, unsigned int mapSizeX, unsigned int mapSizeY, sf::Texture tileSet, std::vector<std::vector<Tile> >& tiles, float posX = 0, float posY = 0);
    void Render(sf::RenderWindow* pTarget);
    bool CheckSolid(float px, float py) const;
    bool CheckLineSolidColision(float x1, float y1, float x2, float y2);
	Tile GetTile(unsigned int x, unsigned int y) { return mTileVec[y][x]; }

private:
    void UpdateTileSpritePos();

    //Private member variables
    float mPosX, mPosY;							//Position x and y
	unsigned int mTileWidth, mTileHeight;      //Tile width and height in pixles
    unsigned int mMapSizeX, mMapSizeY;			//Map size, in tiles
    sf::Texture mTileSet;
    std::vector<std::vector<Tile> > mTileVec;
};

#endif // TILEENGINE_H_INCLUDED
