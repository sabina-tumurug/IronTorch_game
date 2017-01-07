// IronTorch.cpp : Defines the entry point for the console application.
//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "G_unit.h"
#include <string>
#include "TileMap.h"
#include <fstream>
#include <map>
#include <iostream>

//for debuging
#include <Windows.h>
//////////////
using namespace std;

//Encoutered an enemy. Be ready to battleeeeeeeee
//'Can put battleWindowFileName as a <declare>
void battleStart(sf::RenderWindow* window, string battleWindowFileName/*, CharacterModel *enemy*/, CharacterModel* character)
{
	//ifstream battleWin_File;
	//battleWin_File.open(battleWindowFileName);

	//if (battleWin_File.is_open())
	//{
	//	battleWin_File.close();
	//}

	//Draw new TileMap (battle version)
	//can be adapted to get the level from a file
	const int battleLevel[] =
	{
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	};

	int batlTileWidth = 60;
	int batlTileHeight = 60;

	int batlMapWidth = 20;
	int batlMapWHeight = 10;

	TileMap battleMap;

	if (!battleMap.load(battleWindowFileName, sf::Vector2u(batlTileWidth, batlTileHeight), battleLevel, batlMapWidth, batlMapWHeight))
		return;

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
		/*sf::RectangleShape testShape(sf::Vector2f(20, 20));
		testShape.setPosition(10, 10);
		testShape.setFillColor(sf::Color::Green);*/



		//double the proportions of the sprite
		character->loadToFile();
		
		character->shape->setPosition(200.0f, 200.0f);
		window->clear();
		
		window->draw(battleMap);
		window->draw(*(character->shape));

		window->display();

		/*int test = 0;

		while (test < 10000)
		{
			test++;
		}
		break;*/


	}

	
}

//TODO: to be implemented with G_Unit
bool seeWhatIntersectsIntersects(CharacterModel* character, float point_X, float point_Y,/* const int levelTileMap[]*/ G_Unit gMatrix[200], CharacterModel *enList, int enListCount, sf::RenderWindow *window)
{
	//Get retangle
	//*************
	//TODO: to be replaced with G_Unit
	sf::Vector2i vct = sf::Vector2i();

	vct.x = point_X / 60;
	vct.y = point_Y / 60;

	G_Unit intersectingSprite = gMatrix[vct.x + (vct.y * 20)];

	if (intersectingSprite.containsNPC())
	{

		OutputDebugString(L"It's a monster!!!");
		//eliminateNPC(/*npcList2*/enList, /*npcList2Count*/enListCount, intersectingSprite.getNPC()->getID());

		//delete npc from G_Unit

		battleStart(window, "battle-tileSet.png"/*, CharacterModel *enemy*/, character);

		intersectingSprite.deleteNPC();

	}

	return intersectingSprite.IsBackground;
}
//levelG_UnitMap to be changed from int[] ~> G_Unit[]
bool CollisionDetection(/*sf::RectangleShape &obj*/CharacterModel *character, float moveX, float moveY, /*const int levelG_UnitMap[]*/ G_Unit gMatrix[200], CharacterModel *enList, int enListCount, sf::RenderWindow *window)
{
	//sf::RectangleShape obj = character->shape;
	bool token_result = false;
	//get the new four corners of the sprite, and check if sprite it intersects is background or not
	sf::Vector2f objPoz = character->shape->getPosition();
	sf::Vector2f objSize = character->shape->getSize();
	//1.Get upper left corner
	token_result = seeWhatIntersectsIntersects(character, objPoz.x + moveX, objPoz.y + moveY, /*levelG_UnitMap*/gMatrix, enList, enListCount, window);
	if (!token_result)
		return false;
	//2.Get upper right corner
	token_result = seeWhatIntersectsIntersects(character, objPoz.x + moveX + objSize.x, objPoz.y + moveY, /*levelG_UnitMap*/gMatrix, enList, enListCount, window);
	if (!token_result)
		return false;
	//3.Get lower left corner
	token_result = seeWhatIntersectsIntersects(character, objPoz.x + moveX, objPoz.y + moveY + objSize.y, /*levelG_UnitMap*/gMatrix, enList, enListCount, window);
	if (!token_result)
		return false;
	//4.Get lower right corner
	token_result = seeWhatIntersectsIntersects(character, objPoz.x + moveX + objSize.x, objPoz.y + moveY + objSize.y, /*levelG_UnitMap*/gMatrix, enList, enListCount, window);
	if (!token_result)
		return false;

	return true;
}

bool allowMovement(sf::RectangleShape &obj, float moveX, float moveY, float windowWidth, float windowHeight)
{
	sf::Vector2f pos = obj.getPosition();
	sf::Vector2f siz = obj.getSize();

	//position from sprites base point
	float posX = pos.x;
	float posY = pos.y;

	float sizX = siz.x;
	float sizY = siz.y;

	if (moveX > 0 || moveY > 0) {
		if (posX + moveX + sizX >= windowWidth || posY + moveY + sizY >= windowHeight) {
			//Good luck moving there, YOU REBEL!!
			return false;
		}
	}
	if (moveX < 0 || moveY < 0) {
		if (posX - moveX <= 0 || posY - moveY <= 0) {
			//You want to move your sprite there? NO!!!
			return false;
		}
	}
	if (moveX == 0 && moveY == 0)
		return false;

	//go ahead, Mr.Sprite
	return true;
}


int main()
{

	//Window size
	int windowWidth /*= 1200*/ = 1;
	int windowHeight /*= 600*/ = 1;
	//Experiment with map and fstream
	map<string, string> windowMap;
	ifstream mainWindowFile;
	mainWindowFile.open("MAIN_WINDOW-properties.txt");
	if (mainWindowFile.is_open())
	{
		string inLineStr;
		while (getline(mainWindowFile, inLineStr))
		{
			std::size_t found = inLineStr.find('=');
			if (found != std::string::npos)
			{
				string mapKey = inLineStr.substr(0, found);
				string mapVal = inLineStr.substr(found + 1, inLineStr.size() - found);;
				windowMap[mapKey] = mapVal;
			}
		}
		string winHei = windowMap["height"];
		string winWid = windowMap["width"];
		windowHeight = std::stoi(winHei);
		windowWidth = std::stoi(winWid);
		mainWindowFile.close();
	}
	else
		cout << "Unable to open main window properties file\n";

	//////////////////////////////////
	//Map tile size
	int tileWidth = 60;
	int tileHeight = 60;
	//Character size
	float characterWidth = 40;
	//float characterHeight = 60;
	//changed hight for testing
	float characterHeight = 50;

	//Map size (maybe DEFINE it as a CONSTANT
	const int mapSizeHeight = 10;
	const int mapSizeWidth = 20;

	G_Unit g_unitMatrix[200]; 

	//Sprites
	string IrondhulLeftTexture_path = "left.png";
	string IrondhulRightTexture_path = "right.png";
	string vampTexture_path = "vampire(left).png";
	string zombieTexture_path = "zombie(right).png";
	string bossTexture_path = "death.png";
	
	//Theme song
	/*sf::Music music;
	if (!music.openFromFile("theme_song.wav"))
	return -1;
	music.setLoop(true);
	music.play();
	music.setVolume(20);*/

	sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight), "!!IronTorch!!");
	
	//Irondhul properties
	sf::RectangleShape Irondhul(sf::Vector2f(characterWidth, characterHeight));
	Irondhul.setPosition(windowWidth-characterWidth - 5, windowHeight-characterHeight - 5);
	sf::Texture IrondhulTextureLeft;
	IrondhulTextureLeft.loadFromFile(IrondhulLeftTexture_path);
	Irondhul.setTexture(&IrondhulTextureLeft);
	sf::Texture IrondhulTextureRight;
	IrondhulTextureRight.loadFromFile(IrondhulRightTexture_path);

	CharacterModel Irondhul_Ch = CharacterModel("MainCharacter_Irondhul", "Irondhul");
	Irondhul_Ch.shape = &Irondhul;

	//Enemies
	sf::RectangleShape vampire(sf::Vector2f(characterWidth, characterHeight));
	sf::Texture vampireTexture;
	vampireTexture.loadFromFile(vampTexture_path);
	vampire.setTexture(&vampireTexture);

	sf::RectangleShape zombie(sf::Vector2f(characterWidth, characterHeight));
	sf::Texture zombieTexture;
	zombieTexture.loadFromFile(zombieTexture_path);
	zombie.setTexture(&zombieTexture);

	sf::RectangleShape boss(sf::Vector2f(characterWidth, characterHeight));
	sf::Texture bossTexture;
	bossTexture.loadFromFile(bossTexture_path);
	boss.setTexture(&bossTexture);

	//List of NPC-Enemies 

	//zombie#1
	CharacterModel z1 = CharacterModel("1","Zombie");
	z1.shape = &zombie;
	z1.shape->setPosition(sf::Vector2f(1150.0f, 120.0f));

	//zombie#2
	CharacterModel z2 = CharacterModel("2","Zombie");
	z2.cloneShape(z1);
	z2.shape->setPosition(sf::Vector2f(130.0f, 540.0f));

	//zombie#3
	CharacterModel z3 = CharacterModel("3","Zombie");
	z3.cloneShape(z2);
	z3.shape->setPosition(sf::Vector2f(130.0f, 240.0f));

	//zombie#4
	CharacterModel z4 = CharacterModel("4","Zombie");
	z4.cloneShape(z3);
	z4.shape->setPosition(sf::Vector2f(310.0f, 240.0f));

	//vampire#1
	CharacterModel v1 = CharacterModel("5","Vampire");
	v1.shape = &vampire;
	v1.shape->setPosition(sf::Vector2f(310.0f, 420.0f));
	//vampire#2
	CharacterModel v2 = CharacterModel("6","Vampire");
	v2.cloneShape(v1);
	v2.shape->setPosition(sf::Vector2f(1030.0f, 180.0f));
	//vampire#3
	CharacterModel v3 = CharacterModel("7","Vampire");
	v3.cloneShape(v2);
	v3.shape->setPosition(sf::Vector2f(1030.0f, 300.0f));

	//vampire#4
	CharacterModel v4 = CharacterModel("8","Vampire");
	v4.cloneShape(v3);
	v4.shape->setPosition(sf::Vector2f(1150.0f, 420.0f));

	CharacterModel npclist[] =
	/*npcList2[0] = z1;
	npcList2[1] = z2;
	npcList2[2] = z3;
	npcList2[3] = z4;

	npcList2[4] = v1;
	npcList2[5] = v2;
	npcList2[6] = v3;
	npcList2[7] = v4;*/

	{
		z1,z2,z3,z4,v1,v2,v3,v4,
	};
	int npcCount = 8;
	//npcList2Count = 8;

	//Tile map
	const int level[] =
	{
		3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1,
		1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 2, 1, 1, 1, 1, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1,
		2, 0, 1, 1, 1, 1, 1, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1,
		3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
	//dinamicly populate de matrix
	for(int i = 0; i < mapSizeHeight; i++)
		for (int j = 0; j < mapSizeWidth; j++)
		{
			int spriteType = level[j + (i * mapSizeWidth)];
			G_Unit newG;// = G_Unit();
			switch (spriteType)
			{
				//0 = WALL
				case 0:
				{
					newG = G_Unit(tileHeight, tileWidth, j * tileWidth, i * tileHeight, false, "");
					break;
				}
				//1 = CORRIDOR
				case 1:
				{
					newG = G_Unit(tileHeight, tileWidth, j * tileWidth, i * tileHeight, true, "");
					break;
				}
				//2 = CHEST
				case 2:
				{
					newG = G_Unit(tileHeight, tileWidth, j * tileWidth, i * tileHeight, true, "");
					break;
				}
				//3 = DOOR
				case 3:
				{
					newG = G_Unit(tileHeight, tileWidth, j * tileWidth, i * tileHeight, false, "");
					break;
				}
			default:
				break;
			}
			g_unitMatrix[j + (i * mapSizeWidth)] = newG;
		}

	//Map NPC to npc G_unit
	for (int i = 0; i < npcCount/*npcList2Count*/; i++)
	{
		sf::Vector2i vct = sf::Vector2i();

		vct.x = npclist[i].shape->getPosition().x / 60;
		vct.y = npclist[i].shape->getPosition().y / 60;
		/*vct.x = npcList2[i].shape->getPosition().x / 60;
		vct.y = npcList2[i].shape->getPosition().y / 60;*/

		g_unitMatrix[vct.x + (vct.y * 20)].setNPC(&npclist[i]/*&npcList2[i]*/);
	}

	TileMap map;
	if (!map.load("tileset.png", sf::Vector2u(tileWidth, tileHeight), level, mapSizeWidth, mapSizeHeight))
		return -1;
	/////////////////////////////////////////////////////////////////////////////////

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//Irondhul's movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			//battleStart(&window, "battle-tileSet.png");
			if (allowMovement(Irondhul, -0.1f, 0.0f, windowWidth, windowHeight))
			{
				if (CollisionDetection(&Irondhul_Ch, -0.1f, 0.0f, /*level*/ g_unitMatrix, npclist, npcCount, &window))
				{
					Irondhul.move(-0.1f, 0.0f);
					Irondhul.setTexture(&IrondhulTextureLeft);
				}
				
			}

			/*Irondhul.move(-0.1f, 0.0f);
			Irondhul.setTexture(&IrondhulTextureLeft);*/
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			if (allowMovement(Irondhul, 0.0f, 0.1f, windowWidth, windowHeight))
			{
				if (CollisionDetection(&Irondhul_Ch, 0.0f, 0.1f, /*level*/ g_unitMatrix, npclist, npcCount,&window))
				{
					Irondhul.move(0.0f, 0.1f);
				}
				
			}
		}
			
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			if (allowMovement(Irondhul, 0.1f, 0.0f, windowWidth, windowHeight))
			{
				if (CollisionDetection(&Irondhul_Ch, 0.1f, 0.0f, /*level*/ g_unitMatrix, npclist, npcCount, &window))
				{
					Irondhul.move(0.1f, 0.0f);
					Irondhul.setTexture(&IrondhulTextureRight);
				}
				
			}
			/*Irondhul.move(0.1f, 0.0f);
			Irondhul.setTexture(&IrondhulTextureRight);*/
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			if (allowMovement(Irondhul, 0.f, -0.1f, windowWidth, windowHeight))
			{
				if (CollisionDetection(&Irondhul_Ch, 0.f, -0.1f, /*level*/ g_unitMatrix, npclist, npcCount, &window))
				{
					Irondhul.move(0.0f, -0.1f);
				}
				//Irondhul.move(0.0f, -0.1f);
			}
			//Irondhul.move(0.0f, -0.1f);
		}
		///////////////////////////////////////////////////////

		window.clear();
		window.draw(map);

		//Testing if it is possible to draw the same shape multiple times in different positions
		/*zombie.setPosition(sf::Vector2f(100.0f, 100.0f));
		window.draw(zombie);
		zombie.setPosition(sf::Vector2f(200.0f, 200.0f));
		window.draw(zombie);*/

		//Draw enemies
		/*vampire.setPosition(sf::Vector2f(310.0f, 420.0f));
		window.draw(vampire);
		vampire.setPosition(sf::Vector2f(1030.0f, 180.0f));
		window.draw(vampire);
		vampire.setPosition(sf::Vector2f(1030.0f, 300.0f));
		window.draw(vampire);
		vampire.setPosition(sf::Vector2f(1150.0f, 420.0f));
		window.draw(vampire);

		zombie.setPosition(sf::Vector2f(1150.0f, 120.0f));
		window.draw(zombie);
		zombie.setPosition(sf::Vector2f(130.0f, 540.0f));
		window.draw(zombie);
		zombie.setPosition(sf::Vector2f(130.0f, 240.0f));
		window.draw(zombie);
		zombie.setPosition(sf::Vector2f(310.0f, 240.0f));*/
		//window.draw(zombie);

		for (int en = 0; en < /*npcList2Count*/npcCount; en++)
		{
			if(!npclist[en].isDead)
			window.draw(*/*npcList2*/npclist[en].shape);
		}
		///////////////////

		window.draw(Irondhul);
		window.display();
	}
	return 0;
}