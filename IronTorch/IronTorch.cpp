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
#include "Chest.h"
#include "Door.h"

#include <Windows.h>

//////////////
using namespace std;
int CharacterModel::currentId = 0;
int Potion::current_id = 0;
int Chest::currentId = 0;
int Door::currentId = 0;

struct potionAction{
	sf::Text text;
	Potion *potion;
	bool isAttack = false;
};

void battleStart(sf::RenderWindow* window, CharacterModel *enemy, CharacterModel* character, bool isBoss)
{
	float oldChPos_X = character->shape->getPosition().x;
	float oldChPos_Y = character->shape->getPosition().y;

	int batlTileWidth = isBoss ? 128 : 60;
	int batlTileHeight = isBoss ? 128 : 60;

	int batlMapWidth = isBoss ? 10 : 20;
	int batlMapWHeight = isBoss ? 5 : 10;
	character->loadToFile();
	enemy->orientSpriteToLeft();

	sf::Vector2f chPosition;
	chPosition.x = isBoss ? (batlMapWidth / 4 + 1) * batlTileWidth : (batlMapWidth / 4 + 1) * batlTileWidth;
	chPosition.y = isBoss ? (batlMapWHeight / 2) * batlTileHeight : (batlMapWHeight / 2 - 1) * batlTileHeight;

	sf::Vector2f enemyPosition;
	enemyPosition.x = isBoss ? (batlMapWidth - (batlMapWidth / 4 + 1)) * batlTileWidth : (batlMapWidth - (batlMapWidth / 4 + 1)) * batlTileWidth;
	enemyPosition.y = isBoss ? (batlMapWHeight / 2) * batlTileHeight : (batlMapWHeight / 2 - 1) * batlTileHeight;

	//x=6;y=4
	character->shape->setPosition(chPosition);
	enemy->shape->setPosition(enemyPosition);

	character->orientSpriteToRight();

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

	const int bossBattleLevel[] =
	{
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	};

	const int *btlLvlPointer = isBoss ? bossBattleLevel : battleLevel;
	std::string battleMapPath = isBoss ? "bossTileMap.png" : "battle-tileSet.png";

	TileMap battleMap;
	if (!battleMap.load(battleMapPath, sf::Vector2u(batlTileWidth, batlTileHeight), btlLvlPointer, batlMapWidth, batlMapWHeight))
		return;

	//Stat windows
	sf::Text text_chName;
	sf::Text text_enName;

	sf::Font font;
	font.loadFromFile("DancingScript-Regular.ttf");

	// select the font
	text_chName.setFont(font); // font is a sf::Font
						// set the string to display
	text_chName.setString(character->getStats());
	// set the character size
	text_chName.setCharacterSize(24); // in pixels, not points!
	//30.0f - x buffer
	text_chName.setPosition(30.0f, 0.0f);

	text_enName.setFont(font);
	text_enName.setString(enemy->getStats());
	text_enName.setCharacterSize(24);
	text_enName.setPosition(window->getSize().x -200.0f, 0.0f);
	//...
	//Dmg animation
	sf::Texture dmgTexture;
	dmgTexture.loadFromFile("claw-marks.png");
	sf::RectangleShape dmgShape;
	dmgShape.setSize(sf::Vector2f(50.0f, 50.0f));
	dmgShape.setOrigin(dmgShape.getLocalBounds().left + dmgShape.getLocalBounds().width / 2.0f,
		dmgShape.getLocalBounds().top + dmgShape.getLocalBounds().height / 2.0f);
	dmgShape.setTexture(&dmgTexture);

	//Show Attack and Potion list Text
	potionAction actionMatrix[3][3];
	actionMatrix[0][0] = potionAction();
	actionMatrix[0][0].text.setString("Attack");
	actionMatrix[0][0].text.setCharacterSize(20);
	actionMatrix[0][0].text.setFont(font);
	actionMatrix[0][0].text.setPosition(30.0f, (batlMapWHeight - 3)* batlTileHeight);
	actionMatrix[0][0].isAttack = true;

	//Testing text Centering
	sf::FloatRect textRect = actionMatrix[0][0].text.getLocalBounds();
	actionMatrix[0][0].text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);

	int nrOfActions = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i + j != 0)
			{
				if (i * 3 + j <= character->potionList_Size)
				{
					actionMatrix[i][j] = potionAction();
					actionMatrix[i][j].text.setString(character->potionList[i * 3 + j - 1].name.substr(0, 13) + ".");
					actionMatrix[i][j].potion = &(character->potionList[i * 3 + j - 1]);
					actionMatrix[i][j].text.setFont(font);
					actionMatrix[i][j].text.setCharacterSize(20);
					sf::FloatRect textRect = actionMatrix[i][j].text.getLocalBounds();
					actionMatrix[i][j].text.setOrigin(textRect.left + textRect.width / 2.0f,
						textRect.top + textRect.height / 2.0f);
					nrOfActions++;
				}
				else
					actionMatrix[i][j].text.setString("N/A");
			}
		}
	}

	int actionPointer = 0;
	window->setKeyRepeatEnabled(true);
	bool battleIsOver = false;

	bool dmgDone = false;
	bool dmgToCh = false;
	bool isEnemyTurn = false;

	while (window->isOpen() && !battleIsOver)
	{
		sf::Event event;
		if (isEnemyTurn)
		{
			//Attack
			character->combat_defend(enemy->getAttack());
			dmgDone = true;
			dmgToCh = true;
			isEnemyTurn = false;
		}
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			//Key events
			if ((event.type == sf::Event::KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)))
			{
				if (actionPointer == 0)
				{
					actionPointer = nrOfActions - 1;
				}
				else if (actionPointer > 0) actionPointer--;
			}
			if ((event.type == sf::Event::KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)))
			{
				if (actionPointer < 3 * 3 - 3 && actionPointer + 3 <= nrOfActions)
					actionPointer += 3;
			}

			if ((event.type == sf::Event::KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)))
			{
				if (actionPointer == nrOfActions - 1)
				{
					actionPointer = 0;
				}
				else if (actionPointer < nrOfActions - 1) actionPointer++;

			}
			if ((event.type == sf::Event::KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)))
			{
				if (actionPointer >= 3)
				{
					actionPointer -= 3;
				}
			}
			if ((event.type == sf::Event::KeyPressed) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)))
			{
				potionAction selectedAction = actionMatrix[actionPointer / 3][actionPointer % 3];
				if (selectedAction.isAttack)
				{
					//Attack
					enemy->combat_defend(character->getAttack());
					dmgDone = true;
					dmgToCh = false;
					isEnemyTurn = true;

				}
				else {
					character->usePotion(selectedAction.potion->id);
					///////rearange Potions
					for (int i = 0; i < 3; i++)
					{
						for (int j = 0; j < 3; j++)
						{
							if (i + j != 0)
							{
								if (i * 3 + j <= character->potionList_Size)
								{
									actionMatrix[i][j] = potionAction();
									actionMatrix[i][j].text.setString(character->potionList[i * 3 + j - 1].name.substr(0, 13) + ".");
									actionMatrix[i][j].potion = &(character->potionList[i * 3 + j - 1]);
									actionMatrix[i][j].text.setFont(font);
									actionMatrix[i][j].text.setCharacterSize(20);
									sf::FloatRect textRect = actionMatrix[i][j].text.getLocalBounds();
									actionMatrix[i][j].text.setOrigin(textRect.left + textRect.width / 2.0f,
										textRect.top + textRect.height / 2.0f);
								}
								else
									actionMatrix[i][j].text.setString("N/A");
							}
						}
					}
					nrOfActions--;
					if (actionPointer = nrOfActions) actionPointer = nrOfActions - 1;
				}
				//Redraw character UI
				text_chName.setString(character->getStats());
				text_enName.setString(enemy->getStats());
			}
			///end-Key events
		}
		window->clear();
		
		window->draw(battleMap);
		window->draw(*(character->shape));
		window->draw(*(enemy->shape));

		//Stat sections
		window->draw(text_chName);
		window->draw(text_enName);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (actionMatrix[i][j].text.getString() != "N/A")
				{
					sf::RectangleShape sh(sf::Vector2f(/*batlTileWidth * 2, batlTileHeight*/120, 60));

					sh.setPosition((j * 2)* 60, (batlMapWHeight * batlTileHeight) - 60 * (3 - i + isBoss));

					actionMatrix[i][j].text.setPosition((sh.getPosition().x * 2 + sh.getSize().x) / 2, (sh.getPosition().y * 2 + sh.getSize().y) / 2);

					if (actionPointer == i * 3 + j)
					{
						actionMatrix[i][j].text.setFillColor(sf::Color::Yellow);
						actionMatrix[i][j].text.setOutlineColor(sf::Color::Red);
						actionMatrix[i][j].text.setOutlineThickness(1.0f);
					}
					else
					{
						actionMatrix[i][j].text.setFillColor(sf::Color::White);
						actionMatrix[i][j].text.setOutlineColor(sf::Color::Black);
						actionMatrix[i][j].text.setOutlineThickness(0.0f);
					}
					window->draw(actionMatrix[i][j].text);
				}
			}
				
		}
		//show damage animation
		if (dmgDone)
		{
			sf::Vector2f position = dmgToCh ? sf::Vector2f((character->shape->getPosition().x * 2 + character->shape->getSize().x) / 2, (character->shape->getPosition().y * 2 + character->shape->getSize().y) / 2) 
											: sf::Vector2f((enemy->shape->getPosition().x * 2 + enemy->shape->getSize().x) / 2, (enemy->shape->getPosition().y * 2 + enemy->shape->getSize().y) / 2);
			if (dmgToCh)
				dmgShape.setRotation(180.0f);

			dmgShape.setPosition(position);
			dmgDone = false;
			window->draw(dmgShape);

			window->display();
			Sleep(500);
			if (dmgToCh)
			{
				dmgShape.setRotation(180.0f);

				if (character->getHP() <= 0)
				{
					character->isDead = true;
					battleIsOver = true;
					break;
				}
			}
			else
			{
				if (enemy->getHP() <= 0)
				{
					enemy->isDead = true;
					battleIsOver = true;
					break;
				}
			}
		}else
		window->display();
	}
	character->shape->setPosition(sf::Vector2f(oldChPos_X, oldChPos_Y));
}

bool seeWhatIntersectsIntersects(CharacterModel* character, float point_X, float point_Y, G_Unit gMatrix[200],int gMatrixLenght, sf::RenderWindow *window)
{
	sf::Vector2i vct = sf::Vector2i();
	vct.x = point_X / 60;
	vct.y = point_Y / 60;

	G_Unit intersectingSprite = gMatrix[vct.x + (vct.y * 20)];

	if (intersectingSprite.containsNPC())
	{
		CharacterModel *enemy = intersectingSprite.getNPC();
		battleStart(window, enemy, character, false);

		intersectingSprite.deleteNPC();
	}else
		if (intersectingSprite.containsChest())
		{
			Chest* chest = intersectingSprite.getLoot();
			
			//chest->loot
			for (int i = 0; i < chest->loot.size(); i++)
			{
				character->addPotion(chest->loot[i]);
			}
			intersectingSprite.chest->setChestToOpen();

			if (chest->isPrimaryKey)
			{
				for (int d = 0; d < gMatrixLenght; d++)
				{
					if (gMatrix[d].door != nullptr)
					{
						if (gMatrix[d].door->isBossDoor)
						{
							gMatrix[d].openDoor();
						}
					}
				}
			}
		}
		else {
			if (intersectingSprite.containsOpenDoor())
			{
				if (character->shape->getPosition().y < 50)
				{
					CharacterModel boss;
					boss.name = "Death";
					boss.setHP(50);
					boss.setSpritePath_Left("death.png");
					boss.setSpritePath_Right("death.png");
					
					sf::RectangleShape bossSh(sf::Vector2f(40.0f, 60.0f));
					boss.shape = &bossSh;
					boss.orientSpriteToLeft();
					battleStart(window, &boss, character, true);
				}
								return true;

			}
		}

	return intersectingSprite.IsBackground;
}
bool CollisionDetection(CharacterModel *character, float moveX, float moveY, G_Unit gMatrix[200], int gMatrixLenght, sf::RenderWindow *window)
{
	bool token_result = false;
	//get the new four corners of the sprite, and check if sprite it intersects is background or not
	sf::Vector2f objPoz = character->shape->getPosition();
	sf::Vector2f objSize = character->shape->getSize();
	//1.Get upper left corner
	token_result = seeWhatIntersectsIntersects(character, objPoz.x + moveX, objPoz.y + moveY, gMatrix, gMatrixLenght, window);
	if (!token_result)
		return false;
	//2.Get upper right corner
	token_result = seeWhatIntersectsIntersects(character, objPoz.x + moveX + objSize.x, objPoz.y + moveY, gMatrix, gMatrixLenght, window);
	if (!token_result)
		return false;
	//3.Get lower left corner
	token_result = seeWhatIntersectsIntersects(character, objPoz.x + moveX, objPoz.y + moveY + objSize.y, gMatrix, gMatrixLenght, window);
	if (!token_result)
		return false;
	//4.Get lower right corner
	token_result = seeWhatIntersectsIntersects(character, objPoz.x + moveX + objSize.x, objPoz.y + moveY + objSize.y, gMatrix, gMatrixLenght, window);
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
	float characterHeight = 50;

	//Map size (maybe DEFINE it as a CONSTANT)
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
	sf::Music music;
	if (!music.openFromFile("theme_song.wav"))
	return -1;
	music.setLoop(true);
	music.play();
	music.setVolume(50);

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
	Irondhul_Ch.setSpritePath_Left(IrondhulLeftTexture_path);
	Irondhul_Ch.setSpritePath_Right(IrondhulRightTexture_path);

	//Giving Irondhul some potions
	Potion p1 = Potion("Potion of Heath", 10, 0, 0, 0, 0);
	Potion p2 = Potion("Potion of Strength", 0, 7, 0, 0, 0);
	Potion p3 = Potion("Potion of Inteligence", 0, 0, 7, 0, 0);
	Potion p4 = Potion("Potion of Agility", 0, 0, 0, 7, 0);
	Potion p5 = Potion("Potion of Endurance", 0, 0, 0, 0, 7);

	Irondhul_Ch.addPotion(p1);
	Irondhul_Ch.addPotion(p2);
	Irondhul_Ch.addPotion(p3);
	Irondhul_Ch.addPotion(p4);
	Irondhul_Ch.addPotion(p5);
	Irondhul_Ch.setHP(200);

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
	z1.setHP(15);
	z1.strenght = 2;
	z1.inteligence = 2;
	z1.agility = 2;
	z1.endurance = 2;

	z1.shape = &zombie;
	z1.shape->setPosition(sf::Vector2f(1150.0f, 120.0f));
	z1.setSpritePath_Left("zombie(left).png");
	z1.setSpritePath_Right("zombie(right).png");
	z1.orientSpriteToRight();

	//zombie#2
	CharacterModel z2 = CharacterModel("2","Zombie");
	z2.setHP(15);
	z2.strenght = 2;
	z2.inteligence = 2;
	z2.agility = 2;
	z2.endurance = 2;

	z2.cloneShape(z1);
	z2.setSpritePath_Left("zombie(left).png");
	z2.setSpritePath_Right("zombie(right).png");
	z2.orientSpriteToRight();

	z2.shape->setPosition(sf::Vector2f(130.0f, 540.0f));

	//zombie#3
	CharacterModel z3 = CharacterModel("3","Zombie");
	z3.setHP(15);
	z3.strenght = 2;
	z3.inteligence = 2;
	z3.agility = 2;
	z3.endurance = 2;

	z3.cloneShape(z2);
	z3.shape->setPosition(sf::Vector2f(130.0f, 240.0f));
	z3.setSpritePath_Left("zombie(left).png");
	z3.setSpritePath_Right("zombie(right).png");
	z3.orientSpriteToRight();
	
	//zombie#4
	CharacterModel z4 = CharacterModel("4","Zombie");
	z4.setHP(15);
	z4.strenght = 2;
	z4.inteligence = 2;
	z4.agility = 2;
	z4.endurance = 2;

	z4.cloneShape(z3);
	z4.shape->setPosition(sf::Vector2f(310.0f, 240.0f));
	z4.setSpritePath_Left("zombie(left).png");
	z4.setSpritePath_Right("zombie(right).png");
	z4.orientSpriteToRight();

	//vampire#1
	CharacterModel v1 = CharacterModel("5","Vampire");
	v1.setHP(30);
	v1.shape = &vampire;
	v1.shape->setPosition(sf::Vector2f(310.0f, 420.0f));
	v1.setSpritePath_Left("vampire(left).png");
	v1.setSpritePath_Right("vampire(right).png");
	v1.orientSpriteToLeft();

	//vampire#2
	CharacterModel v2 = CharacterModel("6","Vampire");
	v2.setHP(30);
	v2.cloneShape(v1);
	v2.shape->setPosition(sf::Vector2f(1030.0f, 180.0f));
	v2.setSpritePath_Left("vampire(left).png");
	v2.setSpritePath_Right("vampire(right).png");
	v2.orientSpriteToLeft();

	//vampire#3
	CharacterModel v3 = CharacterModel("7","Vampire");
	v3.setHP(30);
	v3.cloneShape(v2);
	v3.shape->setPosition(sf::Vector2f(1030.0f, 300.0f));
	v3.setSpritePath_Left("vampire(left).png");
	v3.setSpritePath_Right("vampire(right).png");
	v3.orientSpriteToLeft();

	//vampire#4
	CharacterModel v4 = CharacterModel("8","Vampire");
	v4.setHP(30);
	v4.cloneShape(v3);
	v4.shape->setPosition(sf::Vector2f(1150.0f, 420.0f));
	v4.setSpritePath_Left("vampire(left).png");
	v4.setSpritePath_Right("vampire(right).png");
	v4.orientSpriteToLeft();

	CharacterModel npclist[] =
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

	//Edit Chests
	Chest chest1;
	sf::RectangleShape chestSh(sf::Vector2f(70.0f, 50.0f));
	sf::Texture chestTexture;
	chestTexture.loadFromFile("chest-close.png");
	chestSh.setTexture(&chestTexture);
	chestSh.setOrigin(chestSh.getLocalBounds().left + chestSh.getLocalBounds().width / 2.0f,
		chestSh.getLocalBounds().top + chestSh.getLocalBounds().height / 2.0f);
	chest1.shape = &chestSh;

	Chest chest2;
	chest2.cloneShape(chest1);
	chest2.isPrimaryKey = true;

	Chest chest3;
	chest3.cloneShape(chest2);

	Chest chest4;
	chest4.cloneShape(chest3);

	Chest chestList[] =
	{
		chest1,chest2,chest3,chest4
	};

	int chestListSize = 4;

	for (int i = 0; i < chestListSize; i++)
	{
		Potion potion("Potion of health#" + to_string(i),
			20,
			0,
			0,
			0,
			0);
		chestList[i].loot.push_back(potion);

	}
	chestList[0].loot.at(0).name = "Potion Extra";
	int chestCursor = 0;

	//Edit doors
	Door door1;
	sf::RectangleShape doorShape(sf::Vector2f(tileWidth, tileHeight));
	sf::Texture doorTexture;
	doorTexture.loadFromFile("door-closed.png");
	doorShape.setTexture(&doorTexture);
	doorShape.setOrigin(doorShape.getLocalBounds().left + doorShape.getLocalBounds().width / 2.0f,
		doorShape.getLocalBounds().top + doorShape.getLocalBounds().height / 2.0f);
	door1.shape = &doorShape;
	door1.isBossDoor = true;

	Door door2;
	door2.cloneShape(door1);
	door2.isBossDoor = false;

	Door doorList[] =
	{
		door1,door2
	};

	int doorListSize = 2;
	int doorListCursor = 0;

	//kind of nasty, but I need to keep it
	G_Unit* enDoor;
	///////
	for(int i = 0; i < mapSizeHeight; i++)
		for (int j = 0; j < mapSizeWidth; j++)
		{
			int spriteType = level[j + (i * mapSizeWidth)];
			G_Unit newG;
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
					chestList[chestCursor].shape->setPosition(j * tileWidth + tileWidth / 2, i * tileHeight + tileHeight / 2);
					newG.chest = &chestList[chestCursor];
					chestCursor++;
					break;
				}
				//3 = DOOR
				case 3:
				{
					newG = G_Unit(tileHeight, tileWidth, j * tileWidth, i * tileHeight, false, "");
					doorList[doorListCursor].shape->setPosition(j * tileWidth + tileWidth / 2, i * tileHeight + tileHeight / 2);
					newG.door = &doorList[doorListCursor];
					if (!newG.door->isBossDoor)
						enDoor = &newG;
					//newG.door->gUnit = &newG;
					doorListCursor++;

					break;
				}
			default:
				break;
			}
			g_unitMatrix[j + (i * mapSizeWidth)] = newG;
		}

	//Map NPC to npc G_unit
	for (int i = 0; i < npcCount; i++)
	{
		sf::Vector2i vct = sf::Vector2i();

		vct.x = npclist[i].shape->getPosition().x / 60;
		vct.y = npclist[i].shape->getPosition().y / 60;

		g_unitMatrix[vct.x + (vct.y * 20)].setNPC(&npclist[i]);
	}

	TileMap map;
	if (!map.load("tileset.png", sf::Vector2u(tileWidth, tileHeight), level, mapSizeWidth, mapSizeHeight))
		return -1;


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
				if (CollisionDetection(&Irondhul_Ch, -0.1f, 0.0f, g_unitMatrix, mapSizeHeight * mapSizeWidth, &window))
				{
					Irondhul.move(-0.1f, 0.0f);
					Irondhul.setTexture(&IrondhulTextureLeft);
				}
				
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			if (allowMovement(Irondhul, 0.0f, 0.1f, windowWidth, windowHeight))
			{
				if (CollisionDetection(&Irondhul_Ch, 0.0f, 0.1f, g_unitMatrix, mapSizeHeight * mapSizeWidth, &window))
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
				if (CollisionDetection(&Irondhul_Ch, 0.1f, 0.0f, g_unitMatrix, mapSizeHeight * mapSizeWidth, &window))
				{
					Irondhul.move(0.1f, 0.0f);
					Irondhul.setTexture(&IrondhulTextureRight);
				}
				
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			if (allowMovement(Irondhul, 0.f, -0.1f, windowWidth, windowHeight))
			{
				if (CollisionDetection(&Irondhul_Ch, 0.f, -0.1f, /*level*/ g_unitMatrix, mapSizeHeight * mapSizeWidth, &window))
				{
					Irondhul.move(0.0f, -0.1f);
				}
			}
		}

		window.clear();
		window.draw(map);

		//Draw Enemies
		int deadEnemies = 0;
		for (int en = 0; en < npcCount; en++)
		{
			if(!npclist[en].isDead)
			window.draw(*npclist[en].shape);
			else deadEnemies++;
		}
			if (deadEnemies == npcCount)
			{
				//door2.openDoor();.
				enDoor->openDoor();
			}

		//Draw chests
		for (int i = 0; i < chestListSize; i++)
		{
			window.draw(*chestList[i].shape);
		}
		//Draw doors
		for (int i = 0; i < doorListSize; i++)
		{
			window.draw(*doorList[i].shape);
		}
		window.draw(Irondhul);
		window.display();
	}
	return 0;
}