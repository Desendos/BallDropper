#include "LevelNormal.h"


LevelNormal::LevelNormal(float x, float y, float z)
{
	sx = x;
	sy = y;
	sz = z;
	pos = dir = Vector(0,0,0);
	textureName = "Images/green.bmp";
}


LevelNormal::~LevelNormal(void)
{
}

void LevelNormal::createPlatformObjects(){

}

