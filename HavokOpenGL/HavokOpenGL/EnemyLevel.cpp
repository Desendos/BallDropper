#include "EnemyLevel.h"


EnemyLevel::EnemyLevel(float x, float y, float z)
{
	sx = x;
	sy = y;
	sz = z;
	pos = dir = Vector(0,0,0);
	textureName = "Images/LavaTexture.bmp";
}


EnemyLevel::~EnemyLevel(void)
{
}


void EnemyLevel::createPlatformObjects(){

}