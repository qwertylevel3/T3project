#include "SkillFactory.h"
#include "Attack.h"
#include "Chant.h"
#include "FireBall.h"

Skill::SkillFactory::SkillFactory()
{
}

Skill::SkillFactory::~SkillFactory()
{
}

void Skill::SkillFactory::init()
{
	FireBall* fireBallPrototype = new FireBall(nullptr);
	Attack* attackPrototype = new Attack(nullptr);
	Chant* chantPrototype = new Chant(nullptr);

	skillPrototypeBox["fireBall"] = fireBallPrototype;
	skillPrototypeBox["attack"] = attackPrototype;
	skillPrototypeBox["chant"] = chantPrototype;
}

Skill::SkillBase* Skill::SkillFactory::getSkill(Character* character,std::string s)
{
//	std::string b=ToolFunction::WStr2UTF8(buffName);
	std::vector<std::string> skillMessage;
	split(s, '_', skillMessage);

	if (skillMessage.empty())
	{
		return nullptr;
	}

	SkillBase* skill = getSkillPrototype(character,skillMessage[0]);
	skillMessage.erase(skillMessage.begin());//remove buff name
	skill->init(skillMessage);
	skill->setID(s);
	return skill;
}

Skill::SkillBase* Skill::SkillFactory::getSkillPrototype(Character* character,const std::string& skillName)
{
	return skillPrototypeBox[skillName]->createPrototype(character);
}

void Skill::SkillFactory::split(std::string s, char splitchar, std::vector<std::string>& vec)
{
	if (vec.size() > 0)//保证vec是空的
		vec.clear();
	int length = s.length();
	int start = 0;
	for (int i = 0; i < length; i++)
	{
		if (s[i] == splitchar && i == 0)//第一个就遇到分割符
		{
			start += 1;
		}
		else if (s[i] == splitchar)
		{
			vec.push_back(s.substr(start, i - start));
			start = i + 1;
		}
		else if (i == length - 1)//到达尾部
		{
			vec.push_back(s.substr(start, i + 1 - start));
		}
	}
}