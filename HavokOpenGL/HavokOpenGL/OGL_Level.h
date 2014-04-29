#pragma once
#include "hvkoglobj.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Box.h"

#include "vector.h"
#include "Level.h"
#include "OGL_Level.h"

class OGL_Level :
	public HvkOGLObj
{
public:
	OGL_Level(Level* hvkBox);
	OGL_Level(Level* hvkBox, char *img);
	~OGL_Level(void);

	Vector verts[8];
	
	void render();
	void setSize(float sx, float sy, float sz);
	void drawFace(int v0, int v1, int v2, int v3);
	//float texture;
	void reloadTextures();
	unsigned int texNum;
	Vector fNorm;
	float mx,my,mz;
};

