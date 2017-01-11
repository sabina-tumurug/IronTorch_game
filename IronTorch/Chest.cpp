#include "Chest.h"


int Chest::getId()
{
	return id;
}

void Chest::setChestToOpen()
{
	shape->setTexture(shapeTexture_Open);
}

void Chest::addLoot(Potion addedLoot)
{
	loot.push_back(addedLoot);
}

Chest::Chest(): id(currentId++)
{
	shapeTexture_Open = &sf::Texture();
	shapeTexture_Close = &sf::Texture();

	shapeTexture_Open->loadFromFile("chest_open.png");
	shapeTexture_Close->loadFromFile("chest-close.png");
	shape = &sf::RectangleShape();

	shape->setTexture(shapeTexture_Close);
}



Chest::~Chest()
{
}
