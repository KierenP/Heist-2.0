#ifndef TILEENGINE_H_INCLUDED
#define TILEENGINE_H_INCLUDED

#include "StaticEntity.h"
#include "FunctionLib.h"
#include "SFML/Graphics.hpp"

//A vector of these will be passed to BaseCharacter. Note it only has the nessisary things to go from tile vec to a path
struct ATile	
{
	float f;
	unsigned int x, y;		
	ATile* Parent;
};

struct Tile : public ATile
{
    sf::Sprite mTileSprite;
    bool mSolidState;
    float g;	
    float h;
    bool Closed;
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
    std::vector<std::vector<Tile> > GetTiles() { return mTiles; }
	sf::Texture GetTexture() { return mTileSet; }

    //Setters
	void SetTileSize(sf::Vector2f val) { mTileSize = val; }
	void SetMapSize(sf::Vector2u val) { mMapSize = val; }
    void SetTiles(std::vector<std::vector<Tile> > pTiles) { mTiles = pTiles; }
	void SetTexture(sf::Texture val) { mTileSet = val; }

    //Public member functions
	void LoadFromFile(std::string pFileLocation);
	void LoadFromParam(sf::Vector2f tileSize, sf::Vector2u mapSize, sf::Texture tileSet, std::vector<std::vector<int> >& tileID, std::vector<std::vector<bool> >& solidLayer);
	void LoadFromTiles(sf::Vector2f tileSize, sf::Vector2u mapSize, sf::Texture tileSet, std::vector<std::vector<Tile> > tiles);

    void Render(sf::RenderWindow* pTarget);
    bool CheckSolid(sf::Vector2f position) const;											//Does a position lie on a solid tile
    bool CheckLineSolidColision(sf::Vector2f point1, sf::Vector2f point2);					//Does a line from point 1 to point 2 cross any solid tiles?
	Tile GetTile(sf::Vector2u position) { return mTiles[position.y][position.x]; }
	std::vector<std::vector<Tile> > PathFind(sf::Vector2u start, sf::Vector2u target);		//Use A* pathfinding to calculate a path from start to target. Return this vector of tiles for use

private:
    void UpdateTileSpritePos();
	bool CheckLineBoxColision(sf::Vector2f point1, sf::Vector2f point2, std::vector<sf::Vector2f> boxPoints);
	void InitialisePathFinding(sf::Vector2u target);
	void CheckNeighbours(std::vector<Tile>& OpenList, unsigned int LowestF);	//Will generate the neibours of a given tile at location (x, y) in Tiles, and add them to OpenList

    //Private member variables
	sf::Vector2f mTileSize;					//Tile width and height in pixles
	sf::Vector2u mMapSize;					//Map size, in tiles
    sf::Texture mTileSet;
	std::vector<std::vector<Tile> > mTiles;
};

#endif // TILEENGINE_H_INCLUDED
