// IronTorch.cpp : Defines the entry point for the console application.
//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "G_unit.h"
#include <string>
#include "TileMap.h"
using namespace std;

////Get the Sprite the point intersects and check if it's background = true;
//TODO: to be implemented with G_Unit
bool seeWhatIntersectsIntersects(float point_X, float point_Y, const int levelTileMap[])
{
	//Get retangle
	//*************
	//TODO: to be replaced with G_Unit
	sf::Vector2i vct = sf::Vector2i();

	vct.x = point_X / /*tileWidth*/ 60;
	vct.y = point_Y / /*tileWidth*/ 60;

	int intersectingSprite = levelTileMap[vct.x + (vct.y * 20)];

	if (intersectingSprite > 0)
		return true;

	return false;
	//***************************************
	//Check if it's background
	//TODO: to be replaced with G_Unit



	//if (futurePosition_X < Xmin || futurePosition_X > Xmax || futurePosition_Y < Ymin || futurePosition_Y > Ymax)
	//{
	//	// Definitely not within the polygon!
	//	return true;
	//}
}
//levelG_UnitMap to be changed from int[] ~> G_Unit[]
bool CollisionDetection(sf::RectangleShape &obj, float moveX, float moveY, const int levelG_UnitMap[])
{
	bool token_result = false;
	//get the new four corners of the sprite, and check if sprite it intersects is background or not
	sf::Vector2f objPoz = obj.getPosition();
	sf::Vector2f objSize = obj.getSize();
	//1.Get upper left corner
	token_result = seeWhatIntersectsIntersects(objPoz.x + moveX, objPoz.y + moveY, levelG_UnitMap);
	if (!token_result)
		return false;
	//2.Get upper right corner
	token_result = seeWhatIntersectsIntersects(objPoz.x + moveX + objSize.x, objPoz.y + moveY, levelG_UnitMap);
	if (!token_result)
		return false;
	//3.Get lower left corner
	token_result = seeWhatIntersectsIntersects(objPoz.x + moveX, objPoz.y + moveY + objSize.y, levelG_UnitMap);
	if (!token_result)
		return false;
	//4.Get lower right corner
	token_result = seeWhatIntersectsIntersects(objPoz.x + moveX + objSize.x, objPoz.y + moveY + objSize.y, levelG_UnitMap);
	if (!token_result)
		return false;
	//// p is your point, p.x is the x coord, p.y is the y coord
	//if (futurePosition_X < Xmin || futurePosition_X > Xmax || futurePosition_Y < Ymin || futurePosition_Y > Ymax) {
	//	// Definitely not within the polygon!
	//	return true;
	//}
	return true;

}

bool allowMovement(sf::RectangleShape &obj, float moveX, float moveY, float windowWidth, float windowHeight)
{
	sf::Vector2f pos = obj.getPosition();
	sf::Vector2f siz = obj.getSize();

	//position from sprites base point
	/*int posX = pos.x;
	int posY = pos.y;*/
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
	music.setVolume(20);

	sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight), "!!IronTorch!!");
	
	//Irondhul properties
	sf::RectangleShape Irondhul(sf::Vector2f(characterWidth, characterHeight));
	Irondhul.setPosition(windowWidth-characterWidth, windowHeight-characterHeight);
	sf::Texture IrondhulTextureLeft;
	IrondhulTextureLeft.loadFromFile(IrondhulLeftTexture_path);
	Irondhul.setTexture(&IrondhulTextureLeft);
	sf::Texture IrondhulTextureRight;
	IrondhulTextureRight.loadFromFile(IrondhulRightTexture_path);

	//Enemies
	sf::RectangleShape vampire(sf::Vector2f(characterWidth, characterHeight));
	sf::Texture vampTexture;
	vampTexture.loadFromFile(vampTexture_path);
	vampire.setTexture(&vampTexture);

	sf::RectangleShape zombie(sf::Vector2f(characterWidth, characterHeight));
	sf::Texture zombieTexture;
	zombieTexture.loadFromFile(zombieTexture_path);
	zombie.setTexture(&zombieTexture);

	sf::RectangleShape boss(sf::Vector2f(characterWidth, characterHeight));
	sf::Texture bossTexture;
	bossTexture.loadFromFile(bossTexture_path);
	boss.setTexture(&bossTexture);

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
	TileMap map;
	if (!map.load("tileset.png", sf::Vector2u(tileWidth, tileHeight), level, 20, 10))
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
				if (CollisionDetection(Irondhul, -0.1f, 0.0f, level))
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
				if (CollisionDetection(Irondhul, 0.0f, 0.1f, level))
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
				if (CollisionDetection(Irondhul, 0.1f, 0.0f, level))
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
				if (CollisionDetection(Irondhul, 0.f, -0.1f, level))
				{
					Irondhul.move(0.0f, -0.1f);
				}
				Irondhul.move(0.0f, -0.1f);
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

		window.draw(Irondhul);
		window.display();
	}
	return 0;
}