#include "EnemyFactoryImplementation.h"


EnemyFactoryImplementation::EnemyFactoryImplementation(void)
{
}


EnemyFactoryImplementation::~EnemyFactoryImplementation(void)
{
}

Enemy* EnemyFactoryImplementation::createEnemy(int enemyType, float x, float y, float z){
	switch(enemyType){
	case BIG:
		return new EnemyBig(x,y,z);
		break;
	case SMALL:
		return new EnemySmall(x,y,z);
		break;
	default: return NULL;
	}
}