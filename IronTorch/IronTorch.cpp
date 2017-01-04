// IronTorch.cpp : Defines the entry point for the console application.
//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "G_unit.h"
#include <string>
#include "TileMap.h"
using namespace std;

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
	float characterHeight = 60;

	//Sprites
	string IrondhulLeftTexture_path = "left.png";
	string IrondhulRightTexture_path = "right.png";
	string vampireTexture_path = "vampire(left).png";
	string zombieTexture_path = "zombie(right).png";
	string bossTexture_path = "death.png";

	//Theme song
	sf::Music music;
	if (!music.openFromFile("theme_song.wav"))
		return -1;
	music.setLoop(true);
	music.play();
	music.setVolume(20);

	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "!!IronTorch!!");

	//Irondhul properties
	sf::RectangleShape Irondhul(sf::Vector2f(characterWidth, characterHeight));
	Irondhul.setPosition(windowWidth - characterWidth, windowHeight - characterHeight);
	sf::Texture IrondhulTextureLeft;
	IrondhulTextureLeft.loadFromFile(IrondhulLeftTexture_path);
	Irondhul.setTexture(&IrondhulTextureLeft);
	sf::Texture IrondhulTextureRight;
	IrondhulTextureRight.loadFromFile(IrondhulRightTexture_path);

	//Enemies
	sf::RectangleShape vampire(sf::Vector2f(characterWidth, characterHeight));
	sf::Texture vampireTexture;
	vampireTexture.loadFromFile(vampireTexture_path);
	vampire.setTexture(&vampireTexture);

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
			Irondhul.move(-0.1f, 0.0f);
			Irondhul.setTexture(&IrondhulTextureLeft);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			Irondhul.move(0.0f, 0.1f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			Irondhul.move(0.1f, 0.0f);
			Irondhul.setTexture(&IrondhulTextureRight);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			Irondhul.move(0.0f, -0.1f);
		///////////////////////////////////////////////////////

		window.clear();
		window.draw(map);

		//Placing enemies
		zombie.setPosition(sf::Vector2f(1150.0f, 120.0f));
		window.draw(zombie);
		zombie.setPosition(sf::Vector2f(130.0f, 540.0f));
		window.draw(zombie);
		zombie.setPosition(sf::Vector2f(130.0f, 240.0f));
		window.draw(zombie);
		zombie.setPosition(sf::Vector2f(310.0f, 240.0f));
		window.draw(zombie);
		vampire.setPosition(sf::Vector2f(310.0f, 420.0f));
		window.draw(vampire);
		vampire.setPosition(sf::Vector2f(1030.0f, 180.0f));
		window.draw(vampire);
		vampire.setPosition(sf::Vector2f(1030.0f, 300.0f));
		window.draw(vampire);
		vampire.setPosition(sf::Vector2f(1150.0f, 420.0f));
		window.draw(vampire);

		window.draw(Irondhul);
		window.display();
	}
	return 0;
}