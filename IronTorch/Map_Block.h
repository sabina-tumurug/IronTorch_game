#pragma once
#include <string>

class Map_Block
{
	//float height, width, position_x, position_y;
	//bool background;
	//std::string path;
public:

	Map_Block();

	void setHeight(float newHeight);
	float getHeight();

	void setWidth(float newWidth);
	float getWidth();

	void setPosition(float newPosition_X, float newPosition_Y);
	float getPosition_X();
	float getPosition_Y();

	void setPath(std::string newPath);
	std::string getPath();

	void setBackground(bool newBackground);
	bool getBackground();

	~Map_Block();
};

