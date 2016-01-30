#include "LevelEntityManager.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void PollEvent(sf::RenderWindow& renderTarget);
void Render(LevelEntityManager& manager, sf::RenderWindow& target);
void Update(LevelEntityManager& manager, KeyState& PressedKeys);
void GenerateTestLevel();
KeyState GetKeyInput();

unsigned int const MapWidth = 30;
unsigned int const MapHeight = 30;

sf::RenderWindow window;
LevelEntityManager TestLevel;
KeyState KeysPressed;

TileEngine MyEngine;

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

	sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Heist", sf::Style::Default, settings);

    GenerateTestLevel();

    while (window.isOpen())
    {
        PollEvent(window);
		Update(TestLevel, KeysPressed);
		Render(TestLevel, window);
    }
}

void GenerateTestLevel()
{
    sf::Texture MyTexture;
    sf::Texture TileSet;

	std::vector<Character> MyPlayerVec;

    MyTexture.loadFromFile("PlaceHolderPlayer.png");
    TileSet.loadFromFile("TileSet.png");

	Character MyPlayer(sf::Vector2f(64, 64), 0, MyTexture, PlayerData(150, 100, 0, GetWeaponStat(SMGWeapon), true));

	MyPlayerVec.push_back(MyPlayer);

	for (int i = 0; i < 1; i++)
	{
		Character MyPlayer2(sf::Vector2f(64, 64), 0, MyTexture, PlayerData(150, -1, 0, GetWeaponStat(SMGWeapon), false));
		MyPlayerVec.push_back(MyPlayer2);

		Character MyPlayer3(sf::Vector2f(64, 64), 0, MyTexture, PlayerData(150, -1, 0, GetWeaponStat(SMGWeapon), false));
		MyPlayerVec.push_back(MyPlayer3);
	}

    std::vector<std::vector<int> > TileIDVec;
    std::vector<std::vector<bool> > SolidStateVec;

    for (unsigned int i = 0; i < MapHeight; i++)
    {
        std::vector<bool> boolRow;
        std::vector<int> intRow;

        for (unsigned int j = 0; j < MapWidth; j++)
        {
            intRow.push_back(rand() % 5);

            if (intRow[j] >= 1)
                intRow[j] = 1;

            if (intRow[j] == 0)
                boolRow.push_back(true);
            else
                boolRow.push_back(false);
        }

        SolidStateVec.push_back(boolRow);
        TileIDVec.push_back(intRow);
    }

    //MyEngine.LoadFromParam(32, 32, MapWidth, MapHeight, TileSet, TileIDVec, SolidStateVec, 0, 0);

    TestLevel.SetPlayers(MyPlayerVec);
    TestLevel.SetTileEngine(MyEngine);
    TestLevel.SetTarget(&window);
	TestLevel.SetSpawnPoint(0, sf::Vector2f(32 * 4, 32 * 4));
	TestLevel.SetSpawnPoint(1, sf::Vector2f(32 * 26, 32 * 25));

	TestLevel.GenerateDustTestLevel();
}

void PollEvent(sf::RenderWindow& renderTarget)
{
    sf::Event event;

	while (renderTarget.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
			renderTarget.close();
    }
}

KeyState GetKeyInput()
{
	KeyState KeyStates;

	KeyStates.LMBPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	KeyStates.LeftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	KeyStates.RightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
	KeyStates.UpPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	KeyStates.DownPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

	return KeyStates;
}

void Update(LevelEntityManager& manager, KeyState& PressedKeys)
{
	PressedKeys = GetKeyInput();

	manager.Update(PressedKeys);
}

void Render(LevelEntityManager& manager, sf::RenderWindow& target)
{
	target.clear();
	manager.Render();
	target.display();
}



