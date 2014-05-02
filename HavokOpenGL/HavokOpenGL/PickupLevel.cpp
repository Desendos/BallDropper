#include "PickupLevel.h"

PickupLevel::PickupLevel(void){

}

PickupLevel::PickupLevel(float x, float y, float z, hkpWorld* world)
{
	sx = x;
	sy = y;
	sz = z;
	pos = dir = Vector(0,0,0);
	textureName = "Images/goldfoil.bmp";
	initFixed(world);
}


PickupLevel::~PickupLevel(void)
{
}


void PickupLevel::createPlatformObjects(){

}