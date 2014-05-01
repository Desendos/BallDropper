#pragma once
#include "level.h"
#include "HavokInit.h"
class IceLevel :
	public Level
{
public:
	IceLevel(void);
	IceLevel(float x, float y, float z, hkpWorld* world);
	~IceLevel(void);
	void createPlatformObjects();
};

