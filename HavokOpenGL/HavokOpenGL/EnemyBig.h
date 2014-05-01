#pragma once
#include "enemy.h"
class EnemyBig :
	public Enemy
{
public:
	EnemyBig(void);
	EnemyBig(float x, float y, float z);
	~EnemyBig(void);
	void output();
	
};

