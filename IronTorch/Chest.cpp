#include "Chest.h"


int Chest::getId()
{
	return id;
}

void Chest::setChestToOpen()
{
	shape->setTexture(&shapeTexture_Open);
}

void Chest::setChestToClose()
{
	shape->setTexture(&shapeTexture_Close);
}

void Chest::addLoot(Potion addedLoot)
{
	loot.push_back(addedLoot);
}

void Chest::cloneShape(const Chest & obj)
{
	shape = new sf::RectangleShape();
	*shape = *obj.shape;
}

Chest::Chest(): id(currentId++)
{
	shapeTexture_Open = sf::Texture();
	shapeTexture_Close = sf::Texture();

	shapeTexture_Open.loadFromFile("chest_open.png");
	shapeTexture_Close.loadFromFile("chest-close.png");
	isEmpty = false;
}



Chest::~Chest()
{
}
