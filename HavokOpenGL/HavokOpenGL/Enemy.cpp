#include "Enemy.h"


Enemy::Enemy(void)
{
	//enemy->LoadMD2Model("Data/Pknight/pknight.md2", "Data/Pknight/pknight.bmp");
	//enemy->pos = Vector(0.0f, 0.0f, 0.0f);	//FIXED position
	//px = py = pz = 0.0;
	
}

Enemy::Enemy(float x, float y, float z)
{
	//enemy->LoadMD2Model("Data/Pknight/pknight.md2", "Data/Pknight/pknight.bmp");
	//enemy->pos = Vector(0.0f, 0.0f, 0.0f);	//FIXED position
	//px = py = pz = 0.0;
	px = x;
	py = y;
	pz = z;
	enemy->pos = Vector(px,py,pz);
}
Enemy::~Enemy(void)
{
}

void Enemy::render(){
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glScalef(0.03,0.03,0.03);
	glTranslatef(enemy->pos.x, enemy->pos.y, enemy->pos.z);	
		glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
		enemy->DisplayMD2(0);  //display frame 0
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Enemy::aiUpdate(Sphere* ball){
	
	//if(ball->getPos().x != px){
	//	enemy->pos = Vector(px-0.1, py, pz);
	//	px = px + 0.1;
	//}
	//hkVector4 vec = ball->getRigidBody()->getPosition();
	//hkVector4 vec2 = hkVector4(0,0,0,0);
	
	if(ball->getRigidBody()->getPosition().getComponent(0) < px){
		px = px - 0.1;
		enemy->pos = Vector(px, py, pz);
	}
	if(ball->getRigidBody()->getPosition().getComponent(0) > px){
		px = px + 0.1;
		enemy->pos = Vector(px, py, pz);
	}
	if(ball->getRigidBody()->getPosition().getComponent(2) < pz){
		pz = pz - 0.1;
		enemy->pos = Vector(px, py, pz);
	}
	if(ball->getRigidBody()->getPosition().getComponent(2) > pz){
		pz = pz + 0.1;
		enemy->pos = Vector(px, py, pz);
	}
	/*}*/
	
}