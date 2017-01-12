#include "Door.h"


void Door::closeDoor()
{
	shape->setTexture(&shapeTexture_Close);
	isOpen = false;

}

void Door::openDoor()
{
	shape->setTexture(&shapeTexture_Open);
	isOpen = true;
}

int Door::getId()
{
	return id;
}

void Door::cloneShape(const Door & obj)
{
	shape = new sf::RectangleShape();
	*shape = *obj.shape;
}

Door::Door() : id(currentId++)
{
	shapeTexture_Open = sf::Texture();
	shapeTexture_Close = sf::Texture();

	shapeTexture_Open.loadFromFile("door-open.png");
	shapeTexture_Close.loadFromFile("door-closed.png");

	isOpen = false;
}


Door::~Door()
{
}
