#ifndef TILEENGINE_H_INCLUDED
#define TILEENGINE_H_INCLUDED

#include "StaticEntity.h"
#include "FunctionLib.h"
#include "SFML/Graphics.hpp"

struct Tile
{
    sf::Sprite mTileSprite;
    bool mSolidState;
	unsigned int x;
	unsigned int y;
    float g;	//everything here and below is for A*
    float h;
    float f;
    bool Closed;
    Tile* Parent;
};

class TileEngine
{
public:
	TileEngine();
    TileEngine(std::string pFileLocation);      //Generate from a file
	TileEngine(sf::Vector2f tileSize, sf::Vector2u mapSize, sf::Texture tileSet, std::vector<std::vector<int> >& tileID, std::vector<std::vector<bool> >& solidLayer);   //Generate from paramiters
	TileEngine(sf::Vector2f tileSize, sf::Vector2u mapSize, sf::Texture tileSet, std::vector<std::vector<Tile> > tiles);												//Generate from already generated Tile vector
    ~TileEngine();

    //Getters
	sf::Vector2f GetTileSize() { return mTileSize; }
	sf::Vector2u GetMapSize() { return mMapSize; }
    std::vector<std::vector<Tile> > GetTiles() { return mTileVec; }
	sf::Texture GetTexture() { return mTileSet; }

    //Setters
	void SetTileSize(sf::Vector2f val) { mTileSize = val; }
	void SetMapSize(sf::Vector2u val) { mMapSize = val; }
    void SetTiles(std::vector<std::vector<Tile> > pTiles) { mTileVec = pTiles; }
	void SetTexture(sf::Texture val) { mTileSet = val; }

    //Public member functions
	void LoadFromFile(std::string pFileLocation);
	void LoadFromParam(sf::Vector2f tileSize, sf::Vector2u mapSize, sf::Texture tileSet, std::vector<std::vector<int> >& tileID, std::vector<std::vector<bool> >& solidLayer);
	void LoadFromTiles(sf::Vector2f tileSize, sf::Vector2u mapSize, sf::Texture tileSet, std::vector<std::vector<Tile> > tiles);

    void Render(sf::RenderWindow* pTarget);
    bool CheckSolid(sf::Vector2f position) const;
    bool CheckLineSolidColision(sf::Vector2f point1, sf::Vector2f point2);
	Tile GetTile(sf::Vector2u position) { return mTileVec[position.y][position.x]; }

private:
    void UpdateTileSpritePos();

    //Private member variables
	sf::Vector2f mTileSize;					//Tile width and height in pixles
	sf::Vector2u mMapSize;					//Map size, in tiles
    sf::Texture mTileSet;
    std::vector<std::vector<Tile> > mTileVec;
};

#endif // TILEENGINE_H_INCLUDED
