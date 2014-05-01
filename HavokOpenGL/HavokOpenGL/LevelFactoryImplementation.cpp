#include "LevelFactoryImplementation.h"


LevelFactoryImplementation::LevelFactoryImplementation(void)
{
}


LevelFactoryImplementation::~LevelFactoryImplementation(void)
{
}

Level* LevelFactoryImplementation::createLevel(int levelType, float x, float y, float z, hkpWorld* world){
	switch(levelType){
	case NormalL: return new LevelNormal(x,y,z,world);
	case EnemyL: return new EnemyLevel(x,y,z,world);
	case IceL: return new IceLevel(x,y,z,world);
	case PickupL: return new PickupLevel(x,y,z,world);
	default: return NULL;
	}
}