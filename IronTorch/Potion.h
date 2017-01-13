#pragma once
#include <string>
class Potion
{
public:
	std::string name;
	//std::string id;
	int id;
	int effectHP;
	int effectStrenght, effectAgility, effectInteligence, effectEndurance;
	static int current_id; 
	Potion();
	Potion(std::string); 
	Potion(std::string, int, int, int, int, int);
	~Potion();
};
