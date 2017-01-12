#pragma once
#include <SFML/Graphics.hpp>
#include "Potion.h"

class Chest
{
public:
	int id;
	sf::Texture shapeTexture_Open;
	sf::Texture shapeTexture_Close;
	static int currentId;
	sf::RectangleShape* shape;
	std::vector<Potion> loot;
	bool isPrimaryKey;

	bool isEmpty;

	int getId();

	void setChestToOpen();
	void setChestToClose();
	void addLoot(Potion);
	
	void cloneShape(const Chest &obj);

	Chest();
	~Chest();
};

