#include "HavokObj.h"

HavokObj::HavokObj(){ 
	rb = NULL; 
	density = 8000;	//nominal value.  Note: steel approx 8000kg/cubic metre
	//friction = 0.2f;
}

HavokObj::~HavokObj(){
	delete rb;
}

void HavokObj::setRigidBodyInfo(hkpWorld *world, hkpShape *hks, float mass, float friction){
	rigidBodyInfo.m_shape = hks;  
	hkpInertiaTensorComputer::setShapeVolumeMassProperties(hks, mass, rigidBodyInfo);
	rigidBodyInfo.m_motionType = hkpMotion::MOTION_DYNAMIC;
	rigidBodyInfo.m_position.set(pos.x, pos.y, pos.z);
	rigidBodyInfo.m_friction = 0.2;
	rigidBodyInfo.m_restitution = 0.6f;
	rb = new hkpRigidBody(rigidBodyInfo);
	hks->removeReference();
	world->addEntity(rb);
	rb->removeReference();

}

void HavokObj::setRigidBodyInfoFixed(hkpWorld *world, hkpShape *hks, float mass){
	rigidBodyInfo.m_shape = hks;  
	hkpInertiaTensorComputer::setShapeVolumeMassProperties(hks, mass, rigidBodyInfo);
	rigidBodyInfo.m_motionType = hkpMotion::MOTION_FIXED;
	rigidBodyInfo.m_position.set(pos.x, pos.y, pos.z);
	rigidBodyInfo.m_friction = 0.2f;
	rigidBodyInfo.m_restitution = 0.6f;
	rb = new hkpRigidBody(rigidBodyInfo);
	hks->removeReference();
	world->addEntity(rb);
	rb->removeReference();
}

void HavokObj::setRigidBodyInfoLessFriction(hkpWorld *world, hkpShape *hks, float mass){
	rigidBodyInfo.m_shape = hks;  
	hkpInertiaTensorComputer::setShapeVolumeMassProperties(hks, mass, rigidBodyInfo);
	rigidBodyInfo.m_motionType = hkpMotion::MOTION_FIXED;
	rigidBodyInfo.m_position.set(pos.x, pos.y, pos.z);
	rigidBodyInfo.m_friction = 0.1;
	rigidBodyInfo.m_restitution = 0.6f;
	rb = new hkpRigidBody(rigidBodyInfo);
	hks->removeReference();
	world->addEntity(rb);
	rb->removeReference();
}

void HavokObj::setRigidBodyInfoSphere(hkpWorld *world, hkpSphereShape *hks, int densityNum){
	rigidBodyInfo.m_shape = hks;
	rigidBodyInfo.m_motionType = hkpMotion::MOTION_DYNAMIC;
	hkpInertiaTensorComputer::setShapeVolumeMassProperties(hks, 1.0f, rigidBodyInfo);
	rigidBodyInfo.m_position.set(1.0, 1.2, 0.0);
	rigidBodyInfo.m_friction = 0.4f;
	rigidBodyInfo.m_restitution = 0.2f;
	density = densityNum;

	rb = new hkpRigidBody(rigidBodyInfo);
	hks->removeReference();
	world->addEntity(rb);
	rb->removeReference();
}

void HavokObj::setPosAfter(){
	rigidBodyInfo.m_position.set(pos.x, pos.y, pos.z);
}

void HavokObj::removeRigidBody(hkpWorld *world){
	world->removeEntity(rb);
	rb = NULL;
	delete rb;
}

//void HavokObj::setFiction(float f){
//	friction = f;
//}