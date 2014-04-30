#pragma once
#include "MD2Model.h"
#include "Sphere.h"
class Enemy
{
public:
	Enemy(void);
	~Enemy(void);
	virtual void output() = 0;
	MD2Model* enemy;
	void render();
	void aiUpdate(Sphere* ball);
	float px,py,pz;
};

