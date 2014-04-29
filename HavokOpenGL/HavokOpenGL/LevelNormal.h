#pragma once
#include "level.h"
class LevelNormal :
	public Level
{
public:
	LevelNormal(void);
	LevelNormal(float x, float y, float z);
	float sx,sy,sz;
	~LevelNormal(void);
	void createPlatformObjects();
	//void initFixed(hkpWorld* world);
};

