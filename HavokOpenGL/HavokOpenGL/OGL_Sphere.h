#pragma once
#include "hvkoglobj.h"
#include "Sphere.h"
#include "Enemy.h"
class OGL_Sphere :
	public HvkOGLObj
{
public:
	OGL_Sphere(Sphere* hvkBox);
	OGL_Sphere(Sphere* hvkBox, char* img);
	~OGL_Sphere(void);

	Vector verts[8];
	
	GLUquadricObj * colSphere; // Collision sphere
	float csRadius;

	void render();
	void setSize(float size);
	bool collisionModel(Enemy* sEnemy, OGL_Sphere * cSphere);
	float px,py,pz;
	float Dx,Dy,Dz;
	float p;
	/*void drawFace(int v0, int v1, int v2, int v3);*/
};

