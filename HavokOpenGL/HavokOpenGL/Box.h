#pragma once
#include "havokobj.h"
class Box :
	public HavokObj
{
public:
	Box(void);
	Box(float sx=0.2f,float sy=0.2f,float sz=0.2f); //default 0.2 cube
	~Box(void);
	void init(hkpWorld* world) ;
	void initFixed(hkpWorld* world) ;
	void initLessFriction(hkpWorld* world) ;
	float sx, sy, sz;
	float friction;
	void setFriction(float f);
	
};

