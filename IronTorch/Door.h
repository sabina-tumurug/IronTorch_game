#pragma once
#include <SFML/Graphics.hpp>

class Door
{
public:
	int id;
	sf::Texture shapeTexture_Open;
	sf::Texture shapeTexture_Close;
	static int currentId;
	sf::RectangleShape* shape;

	bool isBossDoor;

	bool isOpen;
	void closeDoor();
	void openDoor();
	int getId();

	void cloneShape(const Door & obj);

	Door();
	~Door();
};

