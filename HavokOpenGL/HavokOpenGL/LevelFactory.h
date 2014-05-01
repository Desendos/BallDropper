#include "Level.h"
#include "HavokInit.h"
#pragma once

class LevelFactory
{
public:
	LevelFactory(void);
	~LevelFactory(void);
	virtual Level* createLevel(int levelType, float x, float y, float z, hkpWorld* world) = 0;
};

