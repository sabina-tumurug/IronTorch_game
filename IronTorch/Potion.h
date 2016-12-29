#pragma once
#include <string>
class Potion
{
public:
	std::string name;
	int id;

	int effectHP;
	float effectAttack, effectDefence;
	int effectStrenght, effectAgility, effectInteligence, effectEndurance;
	
	Potion();
	Potion(std::string);
	Potion(std::string, int, float,float,int,int,int,int);
	~Potion();
};

