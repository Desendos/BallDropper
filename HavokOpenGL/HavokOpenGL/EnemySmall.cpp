#include "EnemySmall.h"


EnemySmall::EnemySmall(void)
{
	enemy = new MD2Model;
	enemy->LoadMD2Model("Data/pknight/pknight.md2", "Data/pknight/pknight.bmp");
	enemy->pos = Vector(0.0f, 20.0f, 0.0f);	//FIXED position
}


EnemySmall::EnemySmall(float x, float y, float z)
{
	enemy = new MD2Model;
	enemy->LoadMD2Model("Data/laalaa/laalaa.md2", "Data/laalaa/laalaa.bmp");
	px = x;
	py = y;
	pz = z;
	enemy->pos = Vector(px, py, pz);	//FIXED position
	scaler = 0.01;
}


EnemySmall::~EnemySmall(void)
{
}


void EnemySmall::output(){
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