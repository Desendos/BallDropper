#pragma once
#include "platform.h"
#include "HavokObj.h"
#include "OGL_Sphere.h"

class Level : 
	public HavokObj
{
public:
	Level(void);
	Level(float x, float y, float z);
	~Level(void);
	float sx;
	float sy;
	float sz;
	char* textureName;
	virtual void createPlatformObjects() = 0;
	virtual void update(Sphere* spher, OGL_Sphere* ospher,  bool coll) = 0;
	virtual void renderObjects() = 0;
	void init(hkpWorld* world);
	void initFixed(hkpWorld* world);
	void initFixedIce(hkpWorld* world);
	char* getTextureName();
	bool isColliding;
};

