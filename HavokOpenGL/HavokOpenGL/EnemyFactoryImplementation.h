#pragma once
#include "enemyfactory.h"
#include "EnemyBig.h"
#include "EnemySmall.h"
enum enemyTypes{BIG, SMALL};
class EnemyFactoryImplementation :
	public EnemyFactory
{
public:
	EnemyFactoryImplementation(void);
	~EnemyFactoryImplementation(void);
	Enemy* createEnemy(int enemyType);
};

