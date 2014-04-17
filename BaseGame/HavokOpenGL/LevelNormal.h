#pragma once
#include "level.h"
class LevelNormal :
	public Level
{
public:
	LevelNormal(void);
	~LevelNormal(void);
	void createPlatformObjects();
};

