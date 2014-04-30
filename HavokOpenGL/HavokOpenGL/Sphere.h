#pragma once
#include "havokobj.h"
class Sphere :
	public HavokObj
{
private:
	Sphere(float x, float y, float z);
	/*static Sphere* instance;*/
public:
	~Sphere(void);
	void init(hkpWorld* world);
	float sx;
	float sy;
	float sz;
	/*static Sphere* getInstance();*/
};

