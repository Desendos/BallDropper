#pragma once
#include "level.h"
class EnemyLevel :
	public Level
{
public:
	EnemyLevel(void);
	~EnemyLevel(void);
	void createPlatformObjects();
};

