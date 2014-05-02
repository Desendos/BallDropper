#pragma once
#include "enemy.h"
class EnemySmall :
	public Enemy
{
public:
	EnemySmall(void);
	EnemySmall(float x, float y, float z);
	~EnemySmall(void);
	void output();

};

