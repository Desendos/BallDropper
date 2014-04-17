#pragma once
#include "platform.h"
class Level :
	public Platform
{
public:
	Level(void);
	~Level(void);
	virtual void createPlatformObjects() = 0;
};

