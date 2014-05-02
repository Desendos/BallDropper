#include "EnemyBig.h"


EnemyBig::EnemyBig(void)
{
	enemy = new MD2Model;
	enemy->LoadMD2Model("Data/pknight/pknight.md2", "Data/pknight/pknight.bmp");
	//px = 0.0;
	//py = 20.0;
	//pz = 0.0;
	enemy->pos = Vector(px, py, pz);	//FIXED position
}

EnemyBig::EnemyBig(float x, float y, float z)
{
	enemy = new MD2Model;
	enemy->LoadMD2Model("Data/pknight/pknight.md2", "Data/pknight/pknight.bmp");
	px = x;
	py = y;
	pz = z;
	enemy->pos = Vector(px, py, pz);	//FIXED position
	scaler = 0.03;
}


EnemyBig::~EnemyBig(void)
{
}

void EnemyBig::output(){
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glScalef(scaler,scaler,scaler);
	glTranslatef(enemy->pos.x, enemy->pos.y, enemy->pos.z);	
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		enemy->DisplayMD2(0);  //display frame 0
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

