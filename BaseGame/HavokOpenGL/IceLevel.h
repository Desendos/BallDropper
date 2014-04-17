#pragma once
#include "level.h"
class IceLevel :
	public Level
{
public:
	IceLevel(void);
	~IceLevel(void);
	void createPlatformObjects();
};

