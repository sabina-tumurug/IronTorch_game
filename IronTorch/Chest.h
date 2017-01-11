#pragma once
#include <SFML/Graphics.hpp>
#include "Potion.h"

class Chest
{
	sf::Texture* shapeTexture_Open;
	sf::Texture* shapeTexture_Close;

	int id;
public:
	static int currentId;
	sf::RectangleShape* shape;
	std::vector<Potion> loot;

	int getId();

	void setChestToOpen();
	void addLoot(Potion);

	Chest();
	~Chest();
};

