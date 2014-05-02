#include "EnemyLevel.h"


EnemyLevel::EnemyLevel(float x, float y, float z, hkpWorld* world)
{
	sx = x;
	sy = y;
	sz = z;
	pos = dir = Vector(0,0,0);
	textureName = "Images/LavaTexture.bmp";
	initFixed(world); 
	eType = rnd.number(0,1);
	randY = 60;
	enemyFactory = new EnemyFactoryImplementation();
	isColliding = false;
}


EnemyLevel::~EnemyLevel(void)
{
	//delete enemyFactory;
	//if(enemyBig){
	//	delete enemyBig;
	//	enemyBig = NULL;
	//}
	//for(int i = 0; i < SMALL_NUMBER; i++){
	//	if(enemySmall[i]){
	//		delete enemySmall[i];
	//		enemySmall[i] = NULL;
	//	}
	//}
}


void EnemyLevel::createPlatformObjects(){

	randX = rnd.number(-5,5);
	randZ = rnd.number(-5,5);
	if(eType = 0){
		makeBig();
	}
	if(eType = 1){
		enemyBig = enemyFactory->createEnemy(eType, 100, 60, 10);
	}
}

void EnemyLevel::makeBig(){
	if(randX > 2 || randX < -2){
		if(randX > 2 || randX < -2){
			enemyBig = enemyFactory->createEnemy(eType, randX, randY, randZ);
		}
	}
	else{
		createPlatformObjects();
	}
}

void EnemyLevel::makeSmall(){
	for(int i = 0; i < SMALL_NUMBER; i++){
		if(randX > 2 || randX < -2){
			if(randX > 2 || randX < -2){
				enemySmall[i] = enemyFactory->createEnemy(eType, randX, randY, randZ);
				randX = rnd.number(-5,5);
				randZ = rnd.number(-5,5);
			}
		}
		else{
		createPlatformObjects();
		}
	}
}

void EnemyLevel::update(Sphere* spher, OGL_Sphere* ospher,  bool coll){
	/*if(eType = 0){
		enemyBig->aiUpdate(spher);
		isColliding = ospher->collisionModel(enemyBig, ospher);
		if(isColliding == true){
			delete enemyBig;
			enemyBig = NULL;
			coll = true;
		}
	}
	if(eType = 1){
		for(int i = 0; i < SMALL_NUMBER; i++){
			enemySmall[i]->aiUpdate(spher);
			isColliding = ospher->collisionModel(enemySmall[i], ospher);
			if(isColliding == true){
				delete enemySmall[i];
				enemySmall[i] = NULL;
				coll = true;
			}
		}
	}*/

	
}


void EnemyLevel::renderObjects(){
	if(eType = 0){
		enemyBig->render();
	}
	if(eType = 1){
		for(int i = 0; i < SMALL_NUMBER; i++){
			enemySmall[i]->render();
		}
	}
}