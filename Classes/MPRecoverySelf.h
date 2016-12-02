#pragma once

#include "SkillBase.h"

namespace Skill
{
	class MPRecoverySelf:public SkillBase
	{
	public:
		MPRecoverySelf();
		~MPRecoverySelf();
		MPRecoverySelf* createPrototype();
	protected:
		void run();
		void initExtraMessage(std::vector<std::string> extraMessage);
		int value;
	};
}
