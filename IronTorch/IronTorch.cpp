// IronTorch.cpp : Defines the entry point for the console application.
//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "G_unit.h"
#include <string>
#include "TileMap.h"

//for debuging
#include <Windows.h>
//////////////
using namespace std;

//std::vector<CharacterModel> npcList2(10);
//int npcList2Count;

void eliminateNPC(/*std::vector<CharacterModel> npcLst*/ CharacterModel *npcLst, int npcLstCount, int npcID)
{
	for (int nl = 0; nl < npcLstCount; nl++)
	{
		if (npcLst[nl].getID() == npcID)
		{
			if (npcLstCount == 1)
			{
				//npcLst.clear();
				npcLst = NULL;
			}
			else 
				for (int nlDl = nl; nlDl < npcLstCount - 1; nlDl++)
				{
					npcLst[nlDl] = npcLst[nlDl + 1];
				}
			npcLstCount--;
			break;
		}
	}
	
}
////Get the Sprite the point intersects and check if it's background = true;
//TODO: to be implemented with G_Unit
bool seeWhatIntersectsIntersects(float point_X, float point_Y,/* const int levelTileMap[]*/ G_Unit gMatrix[200], CharacterModel *enList, int enListCount)
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
		eliminateNPC(/*npcList2*/enList, /*npcList2Count*/enListCount, intersectingSprite.getNPC()->getID());
		//delete npc from G_Unit
		intersectingSprite.deleteNPC();
	}

	return intersectingSprite.IsBackground;
}
//levelG_UnitMap to be changed from int[] ~> G_Unit[]
bool CollisionDetection(sf::RectangleShape &obj, float moveX, float moveY, /*const int levelG_UnitMap[]*/ G_Unit gMatrix[200], CharacterModel *enList, int enListCount)
{
	bool token_result = false;
	//get the new four corners of the sprite, and check if sprite it intersects is background or not
	sf::Vector2f objPoz = obj.getPosition();
	sf::Vector2f objSize = obj.getSize();
	//1.Get upper left corner
	token_result = seeWhatIntersectsIntersects(objPoz.x + moveX, objPoz.y + moveY, /*levelG_UnitMap*/gMatrix, enList, enListCount);
	if (!token_result)
		return false;
	//2.Get upper right corner
	token_result = seeWhatIntersectsIntersects(objPoz.x + moveX + objSize.x, objPoz.y + moveY, /*levelG_UnitMap*/gMatrix, enList, enListCount);
	if (!token_result)
		return false;
	//3.Get lower left corner
	token_result = seeWhatIntersectsIntersects(objPoz.x + moveX, objPoz.y + moveY + objSize.y, /*levelG_UnitMap*/gMatrix, enList, enListCount);
	if (!token_result)
		return false;
	//4.Get lower right corner
	token_result = seeWhatIntersectsIntersects(objPoz.x + moveX + objSize.x, objPoz.y + moveY + objSize.y, /*levelG_UnitMap*/gMatrix, enList, enListCount);
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
	int windowWidth = 1200;
	int windowHeight = 600;
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
	CharacterModel z1 = CharacterModel(1,"Zombie");
	z1.shape = &zombie;
	z1.shape->setPosition(sf::Vector2f(1150.0f, 120.0f));

	//zombie#2
	CharacterModel z2 = CharacterModel(2,"Zombie");
	z2.cloneShape(z1);
	z2.shape->setPosition(sf::Vector2f(130.0f, 540.0f));

	//zombie#3
	CharacterModel z3 = CharacterModel(3,"Zombie");
	z3.cloneShape(z2);
	z3.shape->setPosition(sf::Vector2f(130.0f, 240.0f));

	//zombie#4
	CharacterModel z4 = CharacterModel(4,"Zombie");
	z4.cloneShape(z3);
	z4.shape->setPosition(sf::Vector2f(310.0f, 240.0f));

	//vampire#1
	CharacterModel v1 = CharacterModel(5,"Vampire");
	v1.shape = &vampire;
	v1.shape->setPosition(sf::Vector2f(310.0f, 420.0f));
	//vampire#2
	CharacterModel v2 = CharacterModel(6,"Vampire");
	v2.cloneShape(v1);
	v2.shape->setPosition(sf::Vector2f(1030.0f, 180.0f));
	//vampire#3
	CharacterModel v3 = CharacterModel(7,"Vampire");
	v3.cloneShape(v2);
	v3.shape->setPosition(sf::Vector2f(1030.0f, 300.0f));

	//vampire#4
	CharacterModel v4 = CharacterModel(8,"Vampire");
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
			if (allowMovement(Irondhul, -0.1f, 0.0f, windowWidth, windowHeight))
			{
				if (CollisionDetection(Irondhul, -0.1f, 0.0f, /*level*/ g_unitMatrix, npclist, npcCount))
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
				if (CollisionDetection(Irondhul, 0.0f, 0.1f, /*level*/ g_unitMatrix, npclist, npcCount))
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
				if (CollisionDetection(Irondhul, 0.1f, 0.0f, /*level*/ g_unitMatrix, npclist, npcCount))
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
				if (CollisionDetection(Irondhul, 0.f, -0.1f, /*level*/ g_unitMatrix, npclist, npcCount))
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
			window.draw(*/*npcList2*/npclist[en].shape);
		}
		///////////////////

		window.draw(Irondhul);
		window.display();
	}
	return 0;
}