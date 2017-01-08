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
CharacterModel::CharacterModel(std::string id, std::string chName)
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
	isDead = false;
	spriteTexture_left = (sf::Texture());
	spriteTexture_right = (sf::Texture());
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
	isDead = false;
	spriteTexture_left = (sf::Texture());
	spriteTexture_right = (sf::Texture());
}

std::string CharacterModel::getID()
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
	potionList.push_back(potion);
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

CharacterModel CharacterModel::loadFromFile(std::string filePath)
{
	CharacterModel result = CharacterModel();

	//be ready for the shape
	//sf::RectangleShape protoShape;
	float shape_height = -0.0f;
	float shape_width = -0.0f;
	float shape_positionX = -0.0f;
	float shape_positionY = -0.0f;


	std::ifstream chStream;
	chStream.open(filePath);
	if (chStream.is_open())
	{
		std::string inLineStr;
		while (std::getline(chStream,inLineStr))
		{
			std::size_t found = inLineStr.find('=');
			if (found != std::string::npos)
			{
				std::string mapKey = inLineStr.substr(0, found);
				std::string mapVal = inLineStr.substr(found + 1, inLineStr.size() - found);
				//can't do a switch ...must do it the good old way .... lot's of ifs
				if (mapKey == "hp")
				{
					result.hp = std::stoi(mapVal);
				}
				else if (mapKey == "id")
				{
					result.ID = std::stoi(mapVal);
				}
				else if (mapKey == "attack")
				{
					result.attack = std::stof(mapVal);
				}
				else if (mapKey == "defence")
				{
					result.defence = std::stof(mapVal);
				}
				else if (mapKey == "strenght")
				{
					result.strenght = std::stoi(mapVal);
				}
				else if (mapKey == "agility")
				{
					result.agility = std::stoi(mapVal);
				}
				else if (mapKey == "inteligence")
				{
					result.inteligence = std::stoi(mapVal);
				}
				else if (mapKey == "endurance")
				{
					result.endurance= std::stoi(mapVal);
				}
				//isDead
				else if (mapKey == "isDead")
				{
					result.isDead= std::stoi(mapVal);
				}
				else if (mapKey == "name")
				{
					result.name= mapVal;
				}
				else if (mapKey == "spritePath_left")
				{
					result.spritePath_left = mapVal;
					//sf::Texture textureLeft;
					//textureLeft.loadFromFile(mapVal);
					//ch->shape->setTexture(&textureRight);

					result.spriteTexture_left.loadFromFile(mapVal);

				}
				else if (mapKey == "spritePath_right")
				{
					result.spritePath_right = mapVal;
					//sf::Texture textureLeft;
					//textureLeft.loadFromFile(mapVal);
					//ch->shape->setTexture(&textureRight);

					result.spriteTexture_right.loadFromFile(mapVal);
				}
				else if (mapKey == "sprite_width")
				{
					shape_width = std::stof(mapVal);
				}
				else if (mapKey == "sprite_height")
				{
					shape_height = std::stof(mapVal);
				}
				else if (mapKey == "sprite_positionX")
				{
					shape_positionX = std::stof(mapVal);
				}
				else if (mapKey == "sprite_positionY")
				{
					shape_positionY = std::stof(mapVal);
				}
				else if
					(mapKey == "potions")
				{
					/////////////
					std::size_t foundStartList = inLineStr.find('[');
					std::size_t foundEndList = inLineStr.find(']');
					if (foundStartList != std::string::npos && foundEndList != std::string::npos)
					{
						/*std::string mapKey = inLineStr.substr(0, found);
						std::string mapVal = inLineStr.substr(found + 1, inLineStr.size() - found);*/
						std::string listString = inLineStr.substr(foundStartList - 1, foundEndList - 1);
						std::vector<Potion> newPotionList;
						//Find all the Potion objects confined in '{' and '}' chars
						while (!listString.empty())
						{
							std::size_t startPotion = listString.find('{');
							std::size_t endPotion = listString.find('}');
							if (startPotion != std::string::npos && endPotion != std::string::npos)
							{
								Potion newPotion = Potion();
								std::string potionStr = listString.substr(startPotion -1, endPotion -1);

								std::vector<std::string> strings;
								std::istringstream f(potionStr);
								std::string s;
								while (std::getline(f, s, ';')) {
									//cout << s << endl;
									strings.push_back(s);
								}
								//go through all attr and fill the potion
								for (int i = 0; i < strings.size(); i++)
								{
									std::size_t foundAtt = strings[i].find('=');
									if (foundAtt != std::string::npos)
									{
										std::string potAttKey = strings[i].substr(0, foundAtt);
										std::string potAttVal = strings[i].substr(foundAtt + 1, strings[i].size() - foundAtt);
										if (potAttKey == "id")
										{
											newPotion.id = std::stoi(potAttVal);
										} 
										else if (potAttKey == "name")
										{
											newPotion.name = potAttVal;
										} 
										else if (potAttKey == "effectHP")
										{
											newPotion.effectHP = std::stoi(potAttVal);
										}
										else if (potAttKey == "effectStrenght")
										{
											newPotion.effectStrenght = std::stoi(potAttVal);
										}
										else if (potAttKey == "effectAgility")
										{
											newPotion.effectAgility = std::stoi(potAttVal);
										}
										else if (potAttKey == "effectInteligence")
										{
											newPotion.effectInteligence = std::stoi(potAttVal);
										}
										else if (potAttKey == "effectEndurance")
										{
											newPotion.effectEndurance = std::stoi(potAttVal);
										}
									}
								}
								//add to Character Potion List
								result.addPotion(newPotion);
							}
						}
						result.potionList_Size = result.potionList.size();
						/////////////
					}
				}
					
			}//end of if(found)
		}
		chStream.close();
	}

	//building the shape
	if (!result.spritePath_right.empty() && !result.spritePath_left.empty() && shape_height >= 0.0f && shape_width >= 0.0f && shape_positionX >= 0.0f && shape_positionY >= 0.0f)
	{
		sf::RectangleShape protoShape(sf::Vector2f(shape_width, shape_height));
		protoShape.setPosition(shape_positionX,shape_positionY);

		sf::Texture protoShape_Texture;
		protoShape_Texture.loadFromFile(result.spritePath_right);
		protoShape.setTexture(&protoShape_Texture);

		result.shape = &protoShape;
	}

	return result;
}

void CharacterModel::loadToFile()
{
	std::ofstream chStream;

	chStream.open("" + ID + ".txt");
	if (chStream.is_open())
	{
		chStream.clear();
		//std::string idAtt = "id=" + ID + "\n";
		//chStream.write("id=" + std::to_string(ID) + "\n", );
		chStream << "id=" << ID << std::endl;
		chStream << "name=" << name << std::endl;
		chStream << "hp=" << std::to_string(hp) << std::endl;
		chStream << "attack=" << std::to_string(attack) << std::endl;
		chStream << "defence=" << std::to_string(defence) << std::endl;
		chStream << "strenght=" << std::to_string(strenght) << std::endl;
		chStream << "agility=" << std::to_string(agility) << std::endl;
		chStream << "inteligence=" << std::to_string(inteligence) << std::endl;
		chStream << "endurance=" << std::to_string(endurance) << std::endl;
		chStream << "isDead=" << std::to_string(isDead) << std::endl;
		chStream << "spritePath_left=" << spritePath_left << std::endl;
		chStream << "spritePath_right=" << spritePath_right << std::endl;
		chStream << "sprite_width=" << shape->getSize().x << std::endl;
		chStream << "sprite_height=" << shape->getSize().y << std::endl;
		chStream << "sprite_positionX" << shape->getPosition().x << std::endl;
		chStream << "sprite_positionY" << shape->getPosition().y << std::endl;


		//The potions
		chStream << "potions=" << "[";
		if (potionList.size() > 0)
		{
			for (int i = 0; i < potionList.size(); i++)
			{
				chStream << "{";
				chStream << "id=" << std::to_string(potionList[i].id) << ";";
				chStream << "name=" << potionList[i].name << ";";
				chStream << "effectHP=" << std::to_string(potionList[i].effectHP) << ";";
				chStream << "effectStrenght=" << std::to_string(potionList[i].effectStrenght) << ";";
				chStream << "effectAgility=" << std::to_string(potionList[i].effectAgility) << ";";
				chStream << "effectInteligence=" << std::to_string(potionList[i].effectInteligence) << ";";
				chStream << "effectEndurance=" << std::to_string(potionList[i].effectEndurance) << ";";
				chStream << "}";

			}
		}
		chStream << "]" << std::endl;



		chStream.close();
	}
}

void CharacterModel::orientSpriteToLeft()
{/*
	sf::Texture textureLeft;
	textureLeft.loadFromFile(spritePath_left);*/

	shape->setTexture(&spriteTexture_left);
}

void CharacterModel::orientSpriteToRight()
{
	//sf::Texture textureRight;
	//textureRight.loadFromFile(spritePath_right);
	//sf::Texture ex1 = *spriteTexture_right;

	shape->setTexture(&spriteTexture_right);
}

void CharacterModel::setSpritePath_Left(std::string const val)
{
	spritePath_left = val;
	//sf::Texture ex;
	//ex.loadFromFile(val);
	spriteTexture_left.loadFromFile(val);
	//spriteTexture_left = &ex;

}

std::string CharacterModel::getSpritePath_Left()
{
	return spritePath_left;
}

void CharacterModel::setSpritePath_Right(std::string const val)
{
	spritePath_right = val;
	//spriteTexture_right->loadFromFile(val);
	//sf::Texture ex;
	//ex.loadFromFile(val);
	spriteTexture_right.loadFromFile(val);
	//spriteTexture_right = ex;
}

std::string CharacterModel::getSpritePath_Right()
{
	return spritePath_right;
}

CharacterModel::~CharacterModel()
{
}
