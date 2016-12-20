// IronTorch.cpp : Defines the entry point for the console application.
//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
using namespace std;

	

int main()
{
	//Window properties
	int windowWidth = 1200;
	int windowHeight = 600;
	
	//Irondhul (main character) graphic properties
	float IrondhulWidth = 40;
	float IrondhulHeight = 60;

	//Sprites
	string IrondhulLeftTexture_path = "left.png";
	string IrondhulRightTexture_path = "right.png";
	
	//Theme song
	sf::Music music;
	if (!music.openFromFile("theme_song.wav"))
	return -1;
	music.setLoop(true);
	music.play();
	music.setVolume(20);

	sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight), "!!IronTorch!!");
	
	//Irondhul's texture and position
	sf::RectangleShape Irondhul(sf::Vector2f(IrondhulWidth, IrondhulHeight));
	Irondhul.setPosition(1160.0f, 540.0f);
	sf::Texture IrondhulTextureLeft;
	IrondhulTextureLeft.loadFromFile(IrondhulLeftTexture_path);
	Irondhul.setTexture(&IrondhulTextureLeft);
	sf::Texture IrondhulTextureRight;
	IrondhulTextureRight.loadFromFile(IrondhulRightTexture_path);
	
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
		//hhhh

		window.clear();
		window.draw(Irondhul);
		window.display();
	
	}

	return 0;
}


