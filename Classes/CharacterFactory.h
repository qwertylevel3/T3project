#pragma once

#include"Singleton.h"
#include"cocos2d.h"
#include"Character.h"
#include "XMLConfigure.h"

#include"CharacterModel.h"
#include<map>

class CharacterFactory:public XMLConfigure,public Singleton<CharacterFactory>
{
public:
	CharacterFactory();
	~CharacterFactory();
	void init();
	Character* getCharacter(std::string characterName);
protected:
	void initCharacterModel(const std::string fileName);
	void createNextAnimationVector(tinyxml2::XMLElement* root,
		std::string animationName,
		std::vector<std::string>& frameVec);

	std::map<std::string, CharacterModel*> modelMap;
};

