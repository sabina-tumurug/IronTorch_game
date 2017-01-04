#pragma once
#include<string>
class G_Unit
{
public:
	float Height, Width, Position_x, Position_y;
	std::string Path;
	bool IsBackground;
	G_Unit();
	G_Unit(float newHeight, float newWidth, float newPosition_x, float newPosition_y, bool newIsBackground, std::string newPath);
	bool isColiding(float, float);
	float getArea();
	~G_Unit();
};
