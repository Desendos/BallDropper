#pragma once

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "vector.h"
#include "OGL_Box.h"
#include "OGL_Sphere.h"
#include "LoadTextures.h"

class Marker
{
public:
	Marker(float x,float y,float z, char* image);
	~Marker(void);
	
	Vector verts[8];

	void render();
	void setSize(float sx, float sy, float sz);
	void drawFace(int v0, int v1, int v2, int v3);
	void setPos(float x, float y, float z);
	void setRGB(float r, float g, float b);
	bool collides(Marker* mark);
	bool collidesBox(OGL_Box* cbox);
	bool collidesWithSphere(OGL_Sphere* cSphere);
	bool collidesWithSphereAndModel(OGL_Sphere* cSphere, Enemy* cEnemy);
	float sx, sy, sz;
	float px,py,pz;
	float mr, mg, mb;
	float Dx,Dy,Dz;
	Vector pos;
	float p;
	unsigned int texture;
};

