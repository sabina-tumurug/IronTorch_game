#pragma once
#include <string>
class Potion
{
public:
	std::string name;
	int id;

	int effectHP;
	int effectStrenght, effectAgility, effectInteligence, effectEndurance;
	
	Potion();
	Potion(std::string);
	Potion(std::string, int,int,int,int,int);
	~Potion();
};

