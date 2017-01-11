#pragma once
#include<string>
#include "CharacterModel.h"
#include "Chest.h"

class G_Unit
{
private:
	CharacterModel* NPC;

public:
	float Height, Width, Position_x, Position_y;
	std::string Path;
	bool IsBackground;
	Chest* chest;

	G_Unit();
	G_Unit(float newHeight, float newWidth, float newPosition_x, float newPosition_y, bool newIsBackground, std::string newPath);
	bool isColiding(float, float);
	float getArea();

	bool containsNPC();
	CharacterModel* getNPC();
	void setNPC(CharacterModel*);
	void deleteNPC();
	~G_Unit();
};

