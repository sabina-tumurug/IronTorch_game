#include "CharacterModel.h"

void CharacterModel::incrStrenght(int incr)
{
	strenght += incr;
	attack = strenght / 2 + inteligence / 2 + 5;
}

void CharacterModel::incrAgility(int incr)
{
	agility += incr;
	defence = agility / 2 + endurance / 2 + 5;
}

void CharacterModel::incrInteligence(int incr)
{
	inteligence += incr;
	attack = strenght / 2 + inteligence / 2 + 5;
}

void CharacterModel::incrEndurance(int incr)
{
	endurance += incr;
	defence = agility / 2 + endurance / 2 + 5;
}

/*
//HP = Strenght & Endurance
int hp;
//Attack = Strenght & Inteligence
//Defence = Agility & Endurance
float attack, defence;
int strenght, agility, inteligence, endurance;

public:
std::string name;
Potion potionList[100];
int potionList_Size;
*/
CharacterModel::CharacterModel(int id, std::string chName)
{
	name = chName;
	ID = id;
	hp = 100;
	attack = 10.0f;
	defence = 10.0f;

	strenght = 5;
	agility = 5;
	inteligence = 5;
	endurance = 5;

	potionList_Size = 0;
}

CharacterModel::CharacterModel()
{
	name = "n/a";
	ID = -1;
	hp = 100;
	attack = 10.0f;
	defence = 10.0f;

	strenght = 5;
	agility = 5;
	inteligence = 5;
	endurance = 5;

	potionList_Size = 0;
}

int CharacterModel::getID()
{
	return ID;
}

int CharacterModel::getHP()
{
	return hp;
}

float CharacterModel::getAttack()
{
	return attack;
}

float CharacterModel::getDefence()
{
	return defence;
}

void CharacterModel::incrAttribute(std::string attributeName, int incrBy)
{
	if (attributeName.compare("strenght") == 0)
	{
		incrStrenght(incrBy);
		return;
	}
	if (attributeName.compare("agility") == 0)
	{
		incrAgility(incrBy);
		return;
	}
	if (attributeName.compare("inteligence") == 0)
	{
		incrInteligence(incrBy);
		return;
	}
	if (attributeName.compare("endurance") == 0)
	{
		incrEndurance(incrBy);
		return;
	}
	//maybe thorw an exception
}

void CharacterModel::incrMultipleAttributes(int incrStre, int incrAgil, int incrIntel, int incrEndur)
{
	incrStrenght(incrStre);
	incrAgility(incrAgil);
	incrInteligence(incrIntel);
	incrEndurance(incrEndur);
}

void CharacterModel::addPotion(Potion potion)
{
	potionList[potionList_Size] = potion;
	potionList_Size++;

}

void CharacterModel::usePotion(int potionID)
{
	int resultPotionPosition = getPotionPositionByID(potionID);
	if (resultPotionPosition < 0)
	{
		//throw error
		return;
	}
	Potion resultPotion = potionList[resultPotionPosition];
	removePotionAtPosition(resultPotionPosition);

	incrStrenght(resultPotion.effectStrenght);
	incrInteligence(resultPotion.effectInteligence);
	incrAgility(resultPotion.effectAgility);
	incrEndurance(resultPotion.effectEndurance);

	hp += resultPotion.effectHP;
}

int CharacterModel::getPotionPositionByID(int potionID)
{
	int result = -1;
	for (int i = 0; i < potionList_Size; i++)
	{
		if (potionList[i].id == potionID)
		{
			result = i;
			break;
		}
	}
	return result;
}

void CharacterModel::removePotionAtPosition(int potionPosition)
{
	for (int i = potionPosition; i < potionList_Size; i++)
	{
		potionList[i] = potionList[i + 1];
	}
	potionList_Size--;
}

float CharacterModel::combat_attack()
{
	//for now ... will modify considering the other attributes
	return attack;
}

float CharacterModel::combat_defend(float attackPow)
{
	float dmg = defence - attack;

	hp -= dmg;
	return dmg; 
}

void CharacterModel::cloneShape(const CharacterModel &obj)
{
	shape = new sf::RectangleShape();
	*shape = *obj.shape;
}

CharacterModel::~CharacterModel()
{
}
