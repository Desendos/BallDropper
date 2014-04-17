#include "Level.h"
#pragma once

class LevelFactory
{
public:
	LevelFactory(void);
	~LevelFactory(void);
	virtual Level* createLevel(int levelType) = 0;
};

