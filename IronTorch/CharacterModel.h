#pragma once
#include<string>
#include "Potion.h"
#include <SFML/Graphics.hpp>

class CharacterModel
{
private:
	//HP = Strenght & Endurance
	int hp;
	//Attack = Strenght & Inteligence
	//Defence = Agility & Endurance
	float attack, defence;
	int strenght, agility, inteligence, endurance;

	int ID;

	void incrStrenght(int);
	void incrAgility(int);
	void incrInteligence(int);
	void incrEndurance(int);

	int getPotionPositionByID(int);
	void removePotionAtPosition(int);


public:
	std::string name;
	Potion potionList[100];
	int potionList_Size;
	sf::RectangleShape* shape;

	CharacterModel(int id,std::string name);
	CharacterModel();
	int getID();

	int getHP();
	float getAttack();
	float getDefence();
	void incrAttribute(std::string, int);
	void incrMultipleAttributes(int, int, int, int);

	void addPotion(Potion);
	void usePotion(int);

	float combat_attack();
	float combat_defend(float);

	void cloneShape(const CharacterModel &obj);
	~CharacterModel();
};

