#include "TileEngine.h"

TileEngine::~TileEngine()
{

}

TileEngine::TileEngine()
{

}

TileEngine::TileEngine(std::string pFileLocation)
{
    //load from file
}

TileEngine::TileEngine(sf::Vector2f tileSize, sf::Vector2u mapSize, sf::Texture tileSet, std::vector<std::vector<int>>& tileID, std::vector<std::vector<bool>>& solidlayer)
{
	LoadFromParam(tileSize, mapSize, tileSet, tileID, solidlayer);
}

TileEngine::TileEngine(sf::Vector2f tileSize, sf::Vector2u mapSize, sf::Texture tileSet, std::vector<std::vector<Tile>> tiles)
{
	LoadFromTiles(tileSize, mapSize, tileSet, tiles);
}

void TileEngine::LoadFromFile(std::string pFileLocation)
{
	//Load from File
}

void TileEngine::LoadFromParam(sf::Vector2f tileSize, sf::Vector2u mapSize, sf::Texture tileSet, std::vector<std::vector<int> >& tileID, std::vector<std::vector<bool> >& solidLayer)
{
	mTileSize = tileSize;
	mMapSize = mapSize;
	mTileSet = tileSet;

	for (unsigned int i = 0; i < mMapSize.y; i++)
	{
		std::vector<Tile> Row;

		for (unsigned int j = 0; j < mMapSize.x; j++)
		{
			Tile TempTile;

			TempTile.mSolidState = solidLayer[i][j];
			TempTile.mTileSprite.setTexture(mTileSet);
			TempTile.mTileSprite.setTextureRect(sf::IntRect((tileID[i][j] % static_cast<int>(mTileSet.getSize().x / mTileSize.x)) * mTileSize.x, static_cast<int>(tileID[i][j] / (mTileSet.getSize().x / mTileSize.x)) * mTileSize.y, static_cast<int>(mTileSize.x), static_cast<int>(mTileSize.y)));

			Row.push_back(TempTile);
		}

		mTileVec.push_back(Row);
	}

	UpdateTileSpritePos();
}

void TileEngine::LoadFromTiles(sf::Vector2f tileSize, sf::Vector2u mapSize, sf::Texture tileSet, std::vector<std::vector<Tile> > tiles)
{
	mTileSize = tileSize;
	mMapSize = mapSize;
	mTileSet = tileSet;
	mTileVec = tiles;
}


void TileEngine::Render(sf::RenderWindow* pTarget)
{
    for (unsigned int i = 0; i < mMapSize.y; i++)
    {
        for (unsigned int j = 0; j < mMapSize.x; j++)
        {
            pTarget->draw(mTileVec[i][j].mTileSprite);
        }
    }
}

void TileEngine::UpdateTileSpritePos()
{
    for (unsigned int i = 0; i < mMapSize.y; i++)
    {
        for (unsigned int j = 0; j < mMapSize.x; j++)
        {
            mTileVec[i][j].mTileSprite.setPosition(j * mTileSize.x, i * mTileSize.y);
        }
    }
}

bool TileEngine::CheckSolid(sf::Vector2f position) const
{
    if (position.x < 0 || position.y < 0 || position.x > mMapSize.x * mTileSize.x || position.y > mMapSize.y * mTileSize.y)  //If out of the world, colision = true
        return true;

    int TilesX = static_cast<int>(position.x / mTileSize.x);
    int TilesY = static_cast<int>(position.y / mTileSize.y);

    if (mTileVec[TilesY][TilesX].mSolidState)  //guarenteed not to throw out of range exeption because of previous if statement exclusing out of bounds values
        return true;

    return false;
}

bool TileEngine::CheckLineSolidColision(sf::Vector2f point1, sf::Vector2f point2)
{
    for (unsigned int i = 0; i < mTileVec.size(); i++)
    {
		for (unsigned int j = 0; j < mTileVec[i].size(); j++)
        {
            if (mTileVec[i][j].mSolidState)
            {
                std::vector<sf::Vector2f> TilePoints = FunctionLib::GenerateBoxFromDimentions(j * mTileSize.x, i * mTileSize.y, mTileSize.x, mTileSize.y);

                float m = (point1.y - point2.y) / (point1.x - point2.x);    //trying to find equasion of line in form y = mx + b. I have found m
                float b = point1.y - m*point1.x;							//re arange to form b = y - mx, and sub in values for x and y

                std::vector<bool> PointIsAbove;

				for (unsigned int k = 0; k < TilePoints.size(); k++)
                {
                    if (TilePoints[k].x * m + b > TilePoints[k].y)
                        PointIsAbove.push_back(true);
                    else
                        PointIsAbove.push_back(false);
                }

                if (!((PointIsAbove[0] && PointIsAbove[1] && PointIsAbove[2] && PointIsAbove[3]) || (!PointIsAbove[0] && !PointIsAbove[1] && !PointIsAbove[2] && !PointIsAbove[3])))
                {
                    if (!(((point1.x < TilePoints[0].x) && (point2.x < TilePoints[0].x)) || ((point1.x > TilePoints[3].x) && (point2.x > TilePoints[3].x))) && !(((point1.y < TilePoints[0].y) && (point2.y < TilePoints[0].y)) || ((point1.y > TilePoints[3].y) && (point2.y > TilePoints[3].y))))
                    {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}
