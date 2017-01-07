#pragma once
#include<string>
#include "Potion.h"
#include<fstream>
#include <SFML/Graphics.hpp>
#include <sstream>

class CharacterModel
{
private:
	//HP = Strenght & Endurance
	int hp;
	//Attack = Strenght & Inteligence
	//Defence = Agility & Endurance
	float attack, defence;
	int strenght, agility, inteligence, endurance;

	std::string ID;

	void incrStrenght(int);
	void incrAgility(int);
	void incrInteligence(int);
	void incrEndurance(int);

	int getPotionPositionByID(int);
	void removePotionAtPosition(int);

	


public:
	std::string name;
	std::vector<Potion>  potionList;
	int potionList_Size;
	sf::RectangleShape* shape;
	bool isDead;

	std::string spritePath;

	CharacterModel(std::string id,std::string name);
	CharacterModel();
	std::string getID();

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
	CharacterModel static loadFromFile(std::string);
	void loadToFile();
	//DELETE FILES WHEN DECONSTRUCTING
	~CharacterModel();
};

