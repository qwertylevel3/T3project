#pragma once

#include "HudMenu.h"
#include "Singleton.h"

class HudSkillMenu:public HudMenu,public Singleton<HudSkillMenu>
{
public:
	HudSkillMenu();
	~HudSkillMenu();
	void update();
	void addItem(HudMenuItem* item);
protected:
};


