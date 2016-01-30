#ifndef LEVELENTITYMANAGER_H
#define LEVELENTITYMANAGER_H

#include "Character.h"
#include "TileEngine.h"
#include <SFML/Graphics.hpp>

#include <vector>

class LevelEntityManager
{
public:
    LevelEntityManager();
	LevelEntityManager(sf::RenderWindow* pTarget, TileEngine newTileEngine, std::vector<Character> players, std::vector<sf::Vector2f> spawnpoints);
    ~LevelEntityManager();

    sf::RenderWindow* GetRenderTarget() { return mRenderTarget; }
    TileEngine& GetTileEngine() { return mTileEngine; }
    std::vector<Character> GetPlayers() { return mPlayerVec; }
    std::vector<sf::Vector2f> GetSpawnPoints() { return mSpawnPoints; }

    void SetTarget(sf::RenderWindow* val) { mRenderTarget = val; }
    void SetTileEngine(TileEngine val) { mTileEngine = val; }
    void SetPlayers(std::vector<Character> val) { mPlayerVec = val; }
	void SetSpawnPoints(std::vector<sf::Vector2f> val) { mSpawnPoints = val; }

    void Render();
    void Update(KeyState pKeyState);
    void AddPlayer(Character val) { mPlayerVec.push_back(val); }
    void SetSpawnPoint(unsigned int index, sf::Vector2f point);
	Character GetPlayer(unsigned int index) { return mPlayerVec[index]; }
	sf::Vector2f GetSpawnPoint(unsigned int index) { return mSpawnPoints[index]; }
	bool CheckTileSolidColision(std::vector<sf::Vector2f> cornerPoints) const;

	void GenerateDustTestLevel();

private:
    sf::Vector2f GetPlayerNewPosition(Character& Player, KeyState moveDirection);
    sf::Vector2f GetBulletNewPosition(Projectile& projectile);
	sf::Vector2f GenerateAiDirection(Character* pCharacter, KeyState moveDirection);
    KeyState AiMoveDecide(Character* pCharacter);
	void CheckBulletColisions(Character& player);
	void InitialiseTiles(std::vector<std::vector<Tile> >& vec, unsigned int TargetTileX, unsigned int TargetTileY);
	void CheckNeibours(std::vector<Tile>& OpenList, std::vector<std::vector<Tile> >& Tiles, unsigned int LowestF);	//Will generate the neibours of a given tile at location (x, y) in Tiles, and add them to OpenList
	bool CalculatePath(std::vector<std::vector<Tile> >& Tiles, unsigned int TargetTileX, unsigned int TargetTileY, unsigned int StartTileX, unsigned int StartTileY);
	KeyState GenerateKeyStateFromPath(std::vector<std::vector<Tile> >& Tiles, unsigned int StartTileX, unsigned int StartTileY, unsigned int TargetTileX, unsigned int TargetTileY, float StartX, float StartY);
	void AllignKeyStateToGrid(KeyState& MoveDirection, unsigned int StartTileX, unsigned int StartTileY, float StartX, float StartY);
	bool GenerateLMBState(Character* pcharacter);

    sf::RenderWindow* mRenderTarget;
    TileEngine mTileEngine;
    std::vector<Character> mPlayerVec;
    sf::View mGameView;
    sf::Clock mFrameClock;
    float mFrameTime;
    std::vector<sf::Vector2f> mSpawnPoints;
};

#endif // LEVELENTITYMANAGER_H
