#pragma once
#include "level.h"
class PickupLevel :
	public Level
{
public:
	PickupLevel(void);
	~PickupLevel(void);
	void createPlatformObjects();
};

