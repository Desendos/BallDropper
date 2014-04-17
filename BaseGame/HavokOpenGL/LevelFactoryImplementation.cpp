#include "LevelFactoryImplementation.h"


LevelFactoryImplementation::LevelFactoryImplementation(void)
{
}


LevelFactoryImplementation::~LevelFactoryImplementation(void)
{
}

Level* LevelFactoryImplementation::createLevel(int levelType){
	switch(levelType){
	case Normal: return new LevelNormal();
	case Enemy: return new EnemyLevel();
	case Ice: return new IceLevel();
	case Pickup: return new PickupLevel();
	default: return NULL;
	}
}