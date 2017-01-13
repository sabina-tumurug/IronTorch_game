#include "Potion.h"

Potion::Potion() : id(current_id++)
{
}

Potion::Potion(std::string newname) : id(current_id++)
{
	name = newname;
	effectHP = 0;
	effectStrenght = 0;
	effectAgility = 0;
	effectInteligence = 0;
	effectEndurance = 0;

	//current_id++;
}
Potion::Potion(std::string newname, int newhp, int neweffectStrenght, int neweffectAgility, int neweffectInteligence, int neweffectEndurance) : id(current_id++)
{
	name = newname;
	effectHP = newhp;
	effectStrenght = neweffectStrenght;
	effectAgility = neweffectAgility;
	effectInteligence = neweffectInteligence;
	effectEndurance = neweffectEndurance;

}
Potion::~Potion()
{
}
