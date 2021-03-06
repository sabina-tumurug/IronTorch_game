#include "G_Unit.h"
#include <string>

G_Unit::G_Unit()
{
	Height = 0.0f;
	Width = 0.0f;
	Path = "";
	Position_x = 0.0f;
	Position_y = 0.0f;
	IsBackground = false;

	NPC = nullptr;
	chest = nullptr;
	door = nullptr;

}

G_Unit::G_Unit(float newHeight, float newWidth, float newPosition_x, float newPosition_y, bool newIsBackground, std::string newPath = "")
{
	Height = newHeight;
	Width = newWidth;
	Path = newPath;
	Position_x = newPosition_x;
	Position_y = newPosition_y;
	IsBackground = newIsBackground;

	NPC = nullptr;
	chest = nullptr;
	door = nullptr;
}

bool G_Unit::isColiding(float pos_x, float pos_y)
{
	return Position_x < pos_x && Position_y < pos_y &&
		Position_x + Width > pos_x &&
		Position_y + Height > pos_y;
}
float G_Unit::getArea()
{
	return Height * Width;
}



Chest * G_Unit::getLoot()
{
	chest->isEmpty = true;
	return chest;
}

bool G_Unit::containsNPC()
{
	if (NPC == nullptr || NPC == NULL) return false;
	return !NPC->isDead;
}

CharacterModel * G_Unit::getNPC()
{
	return NPC;
}

void G_Unit::setNPC(CharacterModel *newNPC)
{
	NPC = newNPC;
}

void G_Unit::deleteNPC()
{
	//delete NPC; //freed memory
	NPC->isDead = true;
	NPC = NULL;
}

bool G_Unit::containsChest()
{
	if (chest == nullptr || chest == NULL) return false;
	else return !chest->isEmpty;
}

bool G_Unit::containsOpenDoor()
{
	if (door == nullptr || door == NULL) return false;
	else return door->isOpen;
}

void G_Unit::openDoor()
{
	if (door != nullptr || door != NULL)
		door->openDoor();
		IsBackground = true;
}

G_Unit::~G_Unit()
{
}
