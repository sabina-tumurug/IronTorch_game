#include "stdafx.h"
#include "Map_Block.h"

#include <string>

class Map_Block
{
public:
	Map_Block::Map_Block()
	{
		height = 0.0;
		width = 0.0;
		position_x = 0.0;
		position_y = 0.0;
		background = false;
		path = "";
	}
	
	Map_Block::Map_Block(float nHeight, float nWidht, float nPosition_X, float nPosition_Y, std::string nPath, bool nBackground = false)
	{
		height = nHeight;
		width = nWidht;
		position_x = nPosition_X;
		position_y = nPosition_Y;
		background = nBackground;
		path = nPath;
	}

	void Map_Block::setHeight(float newHeight)
	{
		height = newHeight;
	}

	float Map_Block::getHeight()
	{
		return height;
	}

	void Map_Block::setWidth(float newWidth)
	{
		width = newWidth;
	}

	float getWidth()
	{
		return width;
	}

	void setPosition(float newPosition_X, float newPosition_Y)
	{
		position_x = newPosition_X;
		position_y = newPosition_Y;
	}
	float getPosition_X()
	{
		return position_x;
	}
	float getPosition_Y()
	{
		return position_y;
	}

	void setPath(std::string newPath)
	{
		path = newPath;
	}
	std::string getPath()
	{
		return path;
	}

	void setBackground(bool newBackground)
	{
		background = newBackground;
	}
	bool getBackground()
	{
		return background;
	}

	~Map_Block() {

	}
private:
	float height, width, position_x, position_y;
	bool background;
	std::string path;
};

