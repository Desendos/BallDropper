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
	isColliding = false;
}


PickupLevel::~PickupLevel(void)
{
}


void PickupLevel::createPlatformObjects(){

}

void PickupLevel::update(Sphere* spher, OGL_Sphere* ospher,  bool coll){

}


void PickupLevel::renderObjects(){

}