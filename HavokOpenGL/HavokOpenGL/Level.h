#pragma once
#include "platform.h"
#include "HavokObj.h"

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
	void init(hkpWorld* world);
	void initFixed(hkpWorld* world);
	char* getTextureName();
};

