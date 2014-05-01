#include "IceLevel.h"


IceLevel::IceLevel(float x, float y, float z, hkpWorld* world)
{
	sx = x;
	sy = y;
	sz = z;
	pos = dir = Vector(0,0,0);
	textureName = "Images/ice.bmp";
	initFixedIce(world);
}


IceLevel::~IceLevel(void)
{
}


void IceLevel::createPlatformObjects(){

}