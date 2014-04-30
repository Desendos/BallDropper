#include "EnemyFactoryImplementation.h"


EnemyFactoryImplementation::EnemyFactoryImplementation(void)
{
}


EnemyFactoryImplementation::~EnemyFactoryImplementation(void)
{
}

Enemy* EnemyFactoryImplementation::createEnemy(int enemyType){
	switch(enemyType){
	case BIG:
		return new EnemyBig;
		break;
	case SMALL:
		return new EnemySmall;
		break;
	default: return NULL;
	}
}