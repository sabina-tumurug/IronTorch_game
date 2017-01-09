#include "Potion.h"

/*
effectAttack, effectDefence;
int effectStrenght, effectAgility, effectInteligence, effectEndurance;
*/
Potion::Potion()
{
}

Potion::Potion(std::string newname)
{
	name = newname;
	effectHP = 0;
	effectStrenght = 0;
	effectAgility = 0;
	effectInteligence = 0;
	effectEndurance = 0;
}
Potion::Potion(std::string newname, int newhp, int neweffectStrenght, int neweffectAgility, int neweffectInteligence, int neweffectEndurance)
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
