#pragma once
#include<string>
#include "Potion.h"
#include<fstream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iomanip>

class CharacterModel
{
private:
	//HP = Strenght & Endurance
	int hp;
	//Attack = Strenght & Inteligence
	//Defence = Agility & Endurance
	float attack, defence;
	int strenght, agility, inteligence, endurance;

	//std::string ID;
	int id;
	void incrStrenght(int);
	void incrAgility(int);
	void incrInteligence(int);
	void incrEndurance(int);

	int getPotionPositionByID(int);
	void removePotionAtPosition(int);

	std::string spritePath_left;
	std::string spritePath_right;


public:
	std::string name;
	std::vector<Potion>  potionList;
	int potionList_Size;
	sf::RectangleShape* shape;
	bool isDead;
	static int currentId;

	sf::Texture spriteTexture_left;
	sf::Texture spriteTexture_right;



	CharacterModel(std::string id, std::string name); /*: id(current_id++) {}*/
	CharacterModel()/*:id(current_id++) {}*/;
	int getId();

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
	void orientSpriteToLeft();
	void orientSpriteToRight();

	void setSpritePath_Left(std::string);
	std::string getSpritePath_Left();
	void setSpritePath_Right(std::string);
	std::string getSpritePath_Right();
	std::string getStats();
	void setHP(int);

	//DELETE FILES WHEN DECONSTRUCTING
	~CharacterModel();
};
//int CharacterModel::currentId = 0;

