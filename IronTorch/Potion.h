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
	static int current_id; // added

						   //patient() : id(current_id++) {} // added
	Potion();/* : id(current_id++) {}*/
	Potion(std::string); /*: id(current_id++) {}*/
	Potion(std::string, int, int, int, int, int); /*: id(current_id++) {}*/
	~Potion();
};
