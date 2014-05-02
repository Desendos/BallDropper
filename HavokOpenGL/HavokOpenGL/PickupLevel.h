#pragma once
#include "level.h"
class PickupLevel :
	public Level
{
public:
	PickupLevel(void);
	PickupLevel(float x, float y, float z, hkpWorld* world);
	~PickupLevel(void);
	void createPlatformObjects();
	void update(Sphere* spher, OGL_Sphere* ospher,  bool coll);
	void renderObjects();
};

