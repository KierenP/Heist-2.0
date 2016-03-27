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

		mTiles.push_back(Row);
	}

	UpdateTileSpritePos();
}

void TileEngine::LoadFromTiles(sf::Vector2f tileSize, sf::Vector2u mapSize, sf::Texture tileSet, std::vector<std::vector<Tile> > tiles)
{
	mTileSize = tileSize;
	mMapSize = mapSize;
	mTileSet = tileSet;
	mTiles = tiles;
}


void TileEngine::Render(sf::RenderWindow* pTarget)
{
    for (unsigned int i = 0; i < mMapSize.y; i++)
    {
        for (unsigned int j = 0; j < mMapSize.x; j++)
        {
            pTarget->draw(mTiles[i][j].mTileSprite);
        }
    }
}

void TileEngine::UpdateTileSpritePos()
{
    for (unsigned int i = 0; i < mMapSize.y; i++)
    {
        for (unsigned int j = 0; j < mMapSize.x; j++)
        {
            mTiles[i][j].mTileSprite.setPosition(j * mTileSize.x, i * mTileSize.y);
        }
    }
}

bool TileEngine::CheckSolid(sf::Vector2f position) const
{
    if (position.x < 0 || position.y < 0 || position.x > mMapSize.x * mTileSize.x || position.y > mMapSize.y * mTileSize.y)  //If out of the world, colision = true
        return true;

    int TilesX = static_cast<int>(position.x / mTileSize.x);
    int TilesY = static_cast<int>(position.y / mTileSize.y);

    if (mTiles[TilesY][TilesX].mSolidState)  //guarenteed not to throw out of range exeption because of previous if statement exclusing out of bounds values
        return true;

    return false;
}

bool TileEngine::CheckLineSolidColision(sf::Vector2f point1, sf::Vector2f point2)
{
    for (unsigned int i = 0; i < mTiles.size(); i++)
    {
		for (unsigned int j = 0; j < mTiles[i].size(); j++)
        {
            if (mTiles[i][j].mSolidState)
            {
                std::vector<sf::Vector2f> TilePoints = FunctionLib::GenerateBoxFromDimentions(j * mTileSize.x, i * mTileSize.y, mTileSize.x, mTileSize.y);

				if (CheckLineBoxColision(point1, point2, TilePoints))
					return true;
            }
        }
    }

    return false;
}

std::vector<std::vector<Tile> > TileEngine::PathFind(sf::Vector2u start, sf::Vector2u target)
{
	InitialisePathFinding(target);

	std::vector<Tile> OpenList;

	OpenList.push_back(mTiles[start.y][start.x]);  //Add starting tile to open

	//This should in theory, only need to be a while (true) loop, but to aid in any kind of bug in the pathfinding it will eventually fall out of the loop
	for (unsigned int i = 0; i < mMapSize.x * mMapSize.y; i++)	
	{
		unsigned int LowestF = 0;   //LowestF is the position in the array OpenList of the tile with the lowest F value

		//Find the tile with the lowest f value
		for (unsigned int j = 0; j < OpenList.size(); j++)
		{
			if (OpenList.at(j).f <= OpenList[LowestF].f)
			{
				LowestF = j;
			}
		}

		sf::Vector2u CurrentTile(OpenList[LowestF].y, OpenList[LowestF].x);

		CheckNeighbours(OpenList, LowestF);

		//Now update F values
		for (unsigned int i = 0; i < OpenList.size(); i++)
		{
			OpenList.at(i).f = OpenList.at(i).g + OpenList.at(i).h;
			mTiles[OpenList.at(i).y][OpenList.at(i).x] = OpenList.at(i);
		}

		mTiles[CurrentTile.y][CurrentTile.x].Closed = true;
		OpenList.erase(OpenList.begin() + LowestF);

		if (CurrentTile.x == target.x && CurrentTile.y == target.y)
		{
			return mTiles;
		}

		if (OpenList.size() == 0)
			break;
	}

	return mTiles;	//How will BaseCharacter handle a invalid Tile vector because a route was not found? I dont know
}

bool TileEngine::CheckLineBoxColision(sf::Vector2f point1, sf::Vector2f point2, std::vector<sf::Vector2f> boxPoints)
{
	float m = (point1.y - point2.y) / (point1.x - point2.x);    //trying to find equasion of line in form y = mx + b. I have found m
	float b = point1.y - m*point1.x;							//re arange to form b = y - mx, and sub in values for x and y

	std::vector<bool> PointIsAbove;

	for (unsigned int k = 0; k < boxPoints.size(); k++)
	{
		PointIsAbove.push_back(boxPoints[k].x * m + b > boxPoints[k].y);
	}

	for (int i = 0; i < PointIsAbove.size() - 1; i++) 
	{
		if (PointIsAbove[i] != PointIsAbove[i + 1])
		{
			if (!(((point1.x < boxPoints[i].x) && (point2.x < boxPoints[i].x)) || ((point1.x > boxPoints[i + 1].x) && (point2.x > boxPoints[i + 1].x))) && !(((point1.y < boxPoints[i].y) && (point2.y < boxPoints[i].y)) || ((point1.y > boxPoints[i + 1].y) && (point2.y > boxPoints[i + 1].y))))
			{
				return true;
			}
		}
	}

	//if (!((PointIsAbove[0] && PointIsAbove[1] && PointIsAbove[2] && PointIsAbove[3]) || (!PointIsAbove[0] && !PointIsAbove[1] && !PointIsAbove[2] && !PointIsAbove[3])))
	//{
		//if (!(((point1.x < boxPoints[0].x) && (point2.x < boxPoints[0].x)) || ((point1.x > boxPoints[3].x) && (point2.x > boxPoints[3].x))) && !(((point1.y < boxPoints[0].y) && (point2.y < boxPoints[0].y)) || ((point1.y > boxPoints[3].y) && (point2.y > boxPoints[3].y))))
		//{
			//return true;
		//}
	//}

	//return false;
}

void TileEngine::InitialisePathFinding(sf::Vector2u target)
{
	for (unsigned int i = 0; i < mTiles.size(); i++)
	{
		for (unsigned int j = 0; j < mTiles.at(i).size(); j++)
		{
			mTiles.at(i).at(j).h = (abs(static_cast<int>(target.x) - static_cast<int>(j)) + abs(static_cast<int>(target.y) - static_cast<int>(i))) * 1;  //G value is the distance you must move X from target to tile, and Y, * 1
			mTiles.at(i).at(j).g = 0;
			mTiles.at(i).at(j).f = mTiles.at(i).at(j).g + mTiles.at(i).at(j).h;
			mTiles.at(i).at(j).x = j;
			mTiles.at(i).at(j).y = i;
			mTiles.at(i).at(j).Closed = false;
		}
	}
}

void TileEngine::CheckNeighbours(std::vector<Tile>& OpenList, unsigned int LowestF)
{
	std::vector<Tile> Neighbours;

	if (OpenList[LowestF].x + 1 < mTiles[OpenList[LowestF].y].size())
		Neighbours.push_back(mTiles[OpenList[LowestF].y][OpenList[LowestF].x + 1]);

	if (OpenList[LowestF].x - 1 >= 0)
		Neighbours.push_back(mTiles[OpenList[LowestF].y][OpenList[LowestF].x - 1]);

	if (OpenList[LowestF].y + 1 < mTiles.size())
		Neighbours.push_back(mTiles[OpenList[LowestF].y + 1][OpenList[LowestF].x]);

	if (OpenList[LowestF].y - 1 >= 0)
		Neighbours.push_back(mTiles[OpenList[LowestF].y - 1][OpenList[LowestF].x]);

	for (unsigned int i = 0; i < Neighbours.size(); i++)
	{
		if (!(Neighbours.at(i).Closed || Neighbours.at(i).mSolidState))
		{
			bool IsInOpen = false;

			for (unsigned int j = 0; j < OpenList.size(); j++)
			{
				if (OpenList.at(j).x == Neighbours.at(i).x && OpenList.at(j).y == Neighbours.at(i).y)
				{
					IsInOpen = true;

					if (OpenList[LowestF].g + 10 < Neighbours.at(i).g)  //if true, better path found
					{
						Neighbours.at(i).g = OpenList[LowestF].g + 10;
						Neighbours.at(i).Parent = &OpenList[LowestF];
					}
				}
			}

			if (!IsInOpen)
			{
				Neighbours.at(i).g = OpenList[LowestF].g + 10;
				Neighbours.at(i).Parent = &mTiles[OpenList[LowestF].y][OpenList[LowestF].x];
				OpenList.push_back(Neighbours.at(i));
			}
		}
	}
}
