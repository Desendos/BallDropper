#include "Sphere.h"


Sphere::Sphere(float x, float y, float z)
{
	sx = x;
	sy = y;
	sz = z;
	pos = dir = Vector(0,0,0);
	radius = 0.2;
}


Sphere::~Sphere(void)
{
}

void Sphere::init(hkpWorld *world){
	hkpSphereShape* sphere = new hkpSphereShape(radius);		// convex radius for spheres is exactly the sphere radius

	float calcMass = density * sx * sy * sz;	//mass = density*vol

	sphere->setRadius(0.001f); // adjust the convex radius as req’d
	setRigidBodyInfoSphere(world, sphere);
}

//Sphere* Sphere::getInstance(){
//	//if(instance == NULL){
//	//	instance = new Sphere(0.2,0.2,0.2);
//	//}
//	//return instance;
//}