// IronTorch.cpp : Defines the entry point for the console application.
//

#include <SFML/Graphics.hpp>

int main()
{
	//Window properties
	int windowHeight = 600;
	int windowWidth = 1200;
	//Irondhul (main character) graphic properties
	float IrondhulHeight = 50;
	float IrondhulWidth = 40;
	
	sf::RenderWindow window(sf::VideoMode(windowWidth,windowHeight), "!!IronTorch!!");
	
	sf::RectangleShape Irondhul(sf::Vector2f(IrondhulWidth, IrondhulHeight));
	Irondhul.setPosition(1160.0f, 550.0f);
	sf::Texture IrondhulTextureLeft;
	IrondhulTextureLeft.loadFromFile("left.png");

	Irondhul.setTexture(&IrondhulTextureLeft);
	sf::Texture IrondhulTextureRight;
	IrondhulTextureRight.loadFromFile("right.png");
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(Irondhul);
		window.display();
	
	}

	return 0;
}


