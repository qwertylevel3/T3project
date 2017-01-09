#include "AISuccubus.h"
#include "Dungeon.h"
#include "ToolFunction.h"
#include "Player.h"
#include "DialogueSystem.h"
#include "Player.h"
#include "HudMessageBox.h"

using std::placeholders::_1;
using std::placeholders::_2;



AISuccubus::AISuccubus()
{
	isFirst = true;
}


AISuccubus::~AISuccubus()
{
}

void AISuccubus::update()
{
	if (isFirst)
	{
		DialogueSystem::getInstance()->runDialogue("succubusSummon");

		isFirst = false;
	}
//状态
	//0为player周围没有enemy，跟随
	//1为player周围有enemy，保护player
	static int stateFlag = 0;

	std::vector<Character* > allEnemy = getEnemyAroundPlayer();
	if (allEnemy.size() == 0)
	{
		//安全
		stateFlag = 0;
	}
	else
	{
		stateFlag = 1;
	}

	if (stateFlag == 0)
	{
		cocos2d::Point playerCoord = Player::getInstance()->getcharacterPtr()->getMapCoord();
		if (ToolFunction::isNear4(characterPtr->getMapCoord(), playerCoord))
		{
			//如果已经靠近了,查找四周的可攻击enemy
			Character* targetCharacter = searchTargetBFS(Character::Bad, 1);
			if (targetCharacter)
			{
				changeOrientationTo(targetCharacter);
				characterPtr->attack();
			}
			else
			{
				characterPtr->idle();
			}
		}
		else
		{
			seek(Player::getInstance()->getcharacterPtr());
		}
	}
	else
	{
		auto bound_cmp = bind(&AISuccubus::cmpDistance, this, _1, _2);
		sort(allEnemy.begin(), allEnemy.end(), bound_cmp);

		Character* enemy = allEnemy[0];

		if (ToolFunction::isNear4(enemy->getMapCoord(),
			characterPtr->getMapCoord()))
		{
			changeOrientationTo(enemy);
			characterPtr->attack();
			return;
		}
		else
		{
			seek(enemy);
			return;
		}
	}



	

//	int viewSize = characterPtr->getViewSize();

//	Character* enemyTarget = searchTargetBFS(Character::Bad);

//	if (enemyTarget)
//	{
//		//如果和player距离过远，就跟随player
//		if (getManhattanDistance(Player::getInstance()->getcharacterPtr()) > 10)
//		{
//			seek(Player::getInstance()->getcharacterPtr());
//		}
//		else
//		{
//			if (isInAttackArea(enemyTarget))
//			{
//				characterPtr->attack();
//			}
//			else
//			{
//				seek(enemyTarget);
//			}
//		}
//	}
//	else
//	{
//		cocos2d::Point playerCoord = Player::getInstance()->getcharacterPtr()->getMapCoord();
//		if (isNear(playerCoord))
//		{
//			characterPtr->idle();
//		}
//		else
//		{
//			seek(Player::getInstance()->getcharacterPtr());
//		}
//	}

}

void AISuccubus::feedback(Character* character)
{
	DialogueSystem::getInstance()->runDialogue("succubusTalk", this->characterPtr);
}

void AISuccubus::handleDialogueResult(std::string dialogueName, int resultNumber)
{
	Player::getInstance()->getcharacterPtr()->sufferHPEffect(-19);
	characterPtr->sufferHPEffect(100);
	characterPtr->sufferMPEffect(100);

	HudMessageBox::getInstance()->addMessage(L"你感觉身体被掏空");

}

std::vector<Character* > AISuccubus::getEnemyAroundPlayer()
{
	std::vector<Character*> allEnemy;

	Field::Storey* storey = Field::Dungeon::getInstance()->getStorey();
	cocos2d::Point oriCoord = Player::getInstance()->getcharacterPtr()->getMapCoord();

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			cocos2d::Point tempCoord = oriCoord;
			tempCoord.x += i;
			tempCoord.y += j;

			Character* target = storey->getCharacter(tempCoord);

			if (target
				&& target->getCharacterType() == Character::Bad)
			{
				allEnemy.push_back(target);
			}
		}
	}
	return allEnemy;
}

bool AISuccubus::cmpDistance(Character* a, Character* b)
{
	return ToolFunction::getManhattanDistance(a->getMapCoord(), characterPtr->getMapCoord())
		< ToolFunction::getManhattanDistance(b->getMapCoord(), characterPtr->getMapCoord());
}
