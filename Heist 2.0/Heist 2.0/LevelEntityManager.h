#ifndef LEVELENTITYMANAGER_H
#define LEVELENTITYMANAGER_H

#include "BaseCharacter.h"
#include "TileEngine.h"
#include <SFML/Graphics.hpp>

#include <vector>

class LevelEntityManager
{
public:
    LevelEntityManager();
	LevelEntityManager(sf::RenderWindow* pTarget, TileEngine newTileEngine, std::vector<BaseCharacter> players, std::vector<sf::Vector2f> spawnpoints);
    ~LevelEntityManager();

    sf::RenderWindow* GetRenderTarget() { return mRenderTarget; }
    TileEngine& GetTileEngine() { return mTileEngine; }
    std::vector<BaseCharacter> GetPlayers() { return mPlayerVec; }
    std::vector<sf::Vector2f> GetSpawnPoints() { return mSpawnPoints; }

    void SetTarget(sf::RenderWindow* val) { mRenderTarget = val; }
    void SetTileEngine(TileEngine val) { mTileEngine = val; }
    void SetPlayers(std::vector<BaseCharacter> val) { mPlayerVec = val; }
	void SetSpawnPoints(std::vector<sf::Vector2f> val) { mSpawnPoints = val; }

    void Render();
    void Update(KeyState pKeyState);
    void AddPlayer(BaseCharacter val) { mPlayerVec.push_back(val); }
    void SetSpawnPoint(unsigned int index, sf::Vector2f point);
	BaseCharacter GetPlayer(unsigned int index) { return mPlayerVec[index]; }
	sf::Vector2f GetSpawnPoint(unsigned int index) { return mSpawnPoints[index]; }

	bool CheckTileSolidColision(std::vector<sf::Vector2f> cornerPoints) const;
	void GenerateDustTestLevel();

private:
    sf::Vector2f GetPlayerNewPosition(BaseCharacter& Player, KeyState moveDirection);
	sf::Vector2f GenerateAiDirection(BaseCharacter* pCharacter, KeyState moveDirection);
    KeyState AiMoveDecide(BaseCharacter* pCharacter);
	void InitialiseTiles(std::vector<std::vector<Tile> >& vec, unsigned int TargetTileX, unsigned int TargetTileY);
	void CheckNeibours(std::vector<Tile>& OpenList, std::vector<std::vector<Tile> >& Tiles, unsigned int LowestF);	//Will generate the neibours of a given tile at location (x, y) in Tiles, and add them to OpenList
	bool CalculatePath(std::vector<std::vector<Tile> >& Tiles, unsigned int TargetTileX, unsigned int TargetTileY, unsigned int StartTileX, unsigned int StartTileY);
	KeyState GenerateKeyStateFromPath(std::vector<std::vector<Tile> >& Tiles, unsigned int StartTileX, unsigned int StartTileY, unsigned int TargetTileX, unsigned int TargetTileY, float StartX, float StartY);
	void AllignKeyStateToGrid(KeyState& MoveDirection, unsigned int StartTileX, unsigned int StartTileY, float StartX, float StartY);
	bool GenerateLMBState(BaseCharacter* pcharacter);

    sf::RenderWindow* mRenderTarget;
    TileEngine mTileEngine;
    std::vector<BaseCharacter> mPlayerVec;
    sf::View mGameView;
    sf::Clock mFrameClock;
    float mFrameTime;
    std::vector<sf::Vector2f> mSpawnPoints;
};

#endif // LEVELENTITYMANAGER_H
