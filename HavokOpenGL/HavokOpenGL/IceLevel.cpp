#include "IceLevel.h"


IceLevel::IceLevel(float x, float y, float z, hkpWorld* world)
{
	sx = x;
	sy = y;
	sz = z;
	pos = dir = Vector(0,0,0);
	textureName = "Images/ice.bmp";
	initFixedIce(world);
	isColliding = false;
}


IceLevel::~IceLevel(void)
{
}


void IceLevel::createPlatformObjects(){

}

void IceLevel::update(Sphere* spher, OGL_Sphere* ospher, bool coll){

}


void IceLevel::renderObjects(){

}