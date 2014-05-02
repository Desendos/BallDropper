#include "LevelNormal.h"


LevelNormal::LevelNormal(float x, float y, float z, hkpWorld* world)
{
	sx = x;
	sy = y;
	sz = z;
	pos = dir = Vector(0,0,0);
	textureName = "Images/green.bmp";
	initFixed(world);
}


LevelNormal::~LevelNormal(void)
{
}

void LevelNormal::createPlatformObjects(){

}

