#pragma once
#include "havokobj.h"
class Sphere :
	public HavokObj
{
private:
	static Sphere* instance;
public:
	Sphere(float x, float y, float z);
	~Sphere(void);
	void init(hkpWorld* world);
	float sx;
	float sy;
	float sz;
	static Sphere* getInstance();
};

