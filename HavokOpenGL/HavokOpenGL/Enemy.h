#pragma once
#include "MD2Model.h"
#include "Sphere.h"

class Enemy
{
public:
	Enemy(void);
	Enemy(float x, float y, float z);
	~Enemy(void);
	virtual void output() = 0;
	MD2Model* enemy;
	void render();
	void aiUpdate(Sphere* ball);
	float px,py,pz;
	float scaler;
//	Timer* enemyTimer;
};

