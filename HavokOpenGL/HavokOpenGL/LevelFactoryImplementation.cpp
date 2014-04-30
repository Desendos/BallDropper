#include "LevelFactoryImplementation.h"


LevelFactoryImplementation::LevelFactoryImplementation(void)
{
}


LevelFactoryImplementation::~LevelFactoryImplementation(void)
{
}

Level* LevelFactoryImplementation::createLevel(int levelType, float x, float y, float z){
	switch(levelType){
	case NormalL: return new LevelNormal(x,y,z);
	case EnemyL: return new EnemyLevel(x,y,z);
	case IceL: return new IceLevel(x,y,z);
	case PickupL: return new PickupLevel(x,y,z);
	default: return NULL;
	}
}