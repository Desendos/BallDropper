#pragma once
#include "Enemy.h"
class EnemyFactory
{
public:
	EnemyFactory(void);
	~EnemyFactory(void);
	virtual Enemy* createEnemy(int enemyType, float x, float y, float z) = 0;
};

