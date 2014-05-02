#pragma once
#include "level.h"
#include "Enemy.h"
#include "random.h"
#include "EnemyFactory.h"
#include "EnemyFactoryImplementation.h"
#include "Game.h"



using namespace random;

const int SMALL_NUMBER = 5;

class EnemyLevel :
	public Level
{
public:
	EnemyLevel(void);
	EnemyLevel(float x, float y, float z, hkpWorld* world);
	~EnemyLevel(void);
	void createPlatformObjects();
	void update();
	EnemyFactory* enemyFactory;
	Enemy* enemyBig;
	Enemy* enemySmall[SMALL_NUMBER];
	void makeSmall();
	void makeBig();
	float randX,randY,randZ;
	int eType;
	void update(Sphere* spher,OGL_Sphere* ospher, bool coll);
	void renderObjects();

};

