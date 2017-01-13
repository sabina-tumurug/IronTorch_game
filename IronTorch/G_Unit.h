#pragma once
#include<string>
#include "CharacterModel.h"
#include "Chest.h"
#include "Door.h"

class G_Unit
{
private:
	CharacterModel* NPC;

public:
	float Height, Width, Position_x, Position_y;
	std::string Path;
	bool IsBackground;
	Chest* chest;
	Door* door;

	G_Unit();
	G_Unit(float newHeight, float newWidth, float newPosition_x, float newPosition_y, bool newIsBackground, std::string newPath);
	bool isColiding(float, float);
	float getArea();

	Chest* getLoot();
	bool containsNPC();
	CharacterModel* getNPC();
	void setNPC(CharacterModel*);
	void deleteNPC();
	bool containsChest();
	bool containsOpenDoor();

	void openDoor();
	~G_Unit();
};

