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
}

G_Unit::G_Unit(float newHeight, float newWidth, float newPosition_x, float newPosition_y, bool newIsBackground, std::string newPath = "")
{
	Height = newHeight;
	Width = newWidth;
	Path = newPath;
	Position_x = newPosition_x;
	Position_y = newPosition_y;
	IsBackground = newIsBackground;
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

G_Unit::~G_Unit()
{
}