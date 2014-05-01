#pragma once
#include "levelfactory.h"
#include "LevelNormal.h"
#include "EnemyLevel.h"
#include "IceLevel.h"
#include "PickupLevel.h"
enum levelTypes {NormalL, EnemyL, IceL, PickupL};
class LevelFactoryImplementation :
	public LevelFactory
{

public:
	LevelFactoryImplementation(void);
	~LevelFactoryImplementation(void);
	Level* createLevel(int levelType, float x, float y, float z, hkpWorld* world);
};

