#include "Level.h"

Level::Level(void){
	//sx = sy = sz = 0;
	sx = 2.0;
	sy = 0.1;
	sz = 2.0;
	pos = dir = Vector(0,0,0);
}

Level::Level(float x, float y, float z)
{
	sx = x;
	sy = y;
	sz = z;
	pos = dir = Vector(0,0,0);
}


Level::~Level(void)
{
}

void Level::init(hkpWorld *world){
	float calcMass = density * sx * sy * sz;	//mass = density*vol
	hkpBoxShape* sBox = new hkpBoxShape(hkVector4(sx, sy, sz));
	sBox->setRadius(0.001f); // adjust the convex radius as req’d
	setRigidBodyInfo(world, sBox, calcMass,0.2);
}

void Level::initFixed(hkpWorld *world){
	float calcMass = density * sx * sy * sz;	//mass = density*vol
	hkpBoxShape* sBox = new hkpBoxShape(hkVector4(sx, sy, sz));
	sBox->setRadius(0.001f); // adjust the convex radius as req’d
	setRigidBodyInfoFixed(world, sBox, calcMass);
}
void Level::initFixedIce(hkpWorld *world){
	float calcMass = density * sx * sy * sz;	//mass = density*vol
	hkpBoxShape* sBox = new hkpBoxShape(hkVector4(sx, sy, sz));
	sBox->setRadius(0.001f); // adjust the convex radius as req’d
	setRigidBodyInfoLessFriction(world, sBox, calcMass);
}

char* Level::getTextureName(){
	return textureName;
}