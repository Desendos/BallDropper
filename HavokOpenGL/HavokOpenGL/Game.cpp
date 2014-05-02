#include "Game.h"
#include "Box.h"

Game::Game(void){
	mouseX = mouseY = 0;
	camX = 0.0f;
	camY = 1.0f;
	camZ = camRad = 1.0f;
	fCount = 0;
	physicsState = false;
	placingWalls = false;
	wallNumber = 0;
	isColliding = false;
	m_sEngine = createIrrKlangDevice();
	m_sEngine->play2D("Sounds/Waterflame - Glorious morning.mp3", true);
	score = -1;
	gameState = 0;
	intCalled = false;
	droppingY = 0.0;
	tiltX = 0;
	tiltZ = 0;
	sphereInZone= false;
	lives = 3;
	sphereDensity = 4000;
	isCollidingModelSphere = false;
}

Game::~Game(void){
	deleteEverything();
}

void Game::InitOpenGL(){
	DebugOut("Game::InitOpenGL being called");
	Set2D();
}

void Game::Initialise(){
	GAMESTATE = MAINSTATESCREEN;
	DebugOut("Game::Initialise being called");
	glEnable(GL_POLYGON_SMOOTH);  //set best smoothing
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	float matSpec[] = {0.0f, 1.0f, 0.0f, 1.0f };
	float matShiny[] = {50.0 };  //128 is max value
	glMaterialfv(GL_FRONT, GL_AMBIENT, matSpec);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShiny);
	lightPos[0]=10; lightPos[1]=-10; lightPos[2]= 10; lightPos[3]=-10.0f;
	float whiteLight[] = {1.0f, 1.0f, 1.0f, 1.0f };
	float ambLight[] = {0.1f, 0.1f, 0.1f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambLight);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	lSphere = gluNewQuadric();	//to show where light pos is
	gluQuadricDrawStyle(lSphere, GLU_FILL);
	gluQuadricNormals(lSphere, GLU_NONE);

	timer = new Timer();
	font1 = new BFont(hDC, "Courier", 14);
	
	//enemyf->enemy->pos = Vector(100.0,0.0,10.0);
}

void Game::Shutdown(){

	DebugOut("Game::Shutdown being called");
	delete timer;
	delete font1;
	loadFileof.close();
	loadFileif.close();
	//enemyf->enemy->
}

void Game::Update(){
	//Timers
	while(timer->getElapsedTime() - lft - 1.0f/60.0f < 0.001f); //Frame Limiter (set to 60 FPS)
	cft = timer->getElapsedTime();
	tbf = cft - lft;
	lft = cft;
	//Havok
	if(GAMESTATE == MAINSTATESCREEN){

	}
	if(GAMESTATE == PLAYSTATESCREEN){
		if(physicsState){
			m_world->stepDeltaTime(tbf); //update physics engine
			#ifdef _DEBUG
				m_vdb->step(tbf);	// update VDB when running
			#endif
		}
		//if(physicsState == true){
		//	if(pBox->getPos().y < -4 /*|| pBoxArray[0]->getPos().y < 6 || pBoxArray[1]->getPos().y < 6 || pBoxArray[2]->getPos().y < 6 || pBoxArray[3]->getPos().y < 6*/){
		//		//physicsState = false;
		//		pBoxArray[0]->getRigidBody()->setPosition(hkVector4(0.0,0.0,0.0));
		//	}
		//}
		//if(pSphere->getPos().y < -10.0){//to stop error
		//	physicsState = false;
		//}
		
		//Object Updates
		if(oSphere){
			oSphere->update();
		}
		if(oLevel1){
			oLevel1->update();
		}
		//Collision dectection
		if(goal && oSphere){
			isColliding = goal->collidesWithSphere(oSphere);
			if(isColliding == true){
				deleteEverything();
				makeGoal();
				deleteLevel1();
				createLevel1();
			}
		}
		if(pSphere->getPos().y <= -15){
			sphereInZone == false;
			if(sphereInZone == false){
					dropSphere();
					lives--;
			}
		}
		if(enemyf){
			enemyf->aiUpdate(pSphere);
			isCollidingModelSphere = oSphere->collisionModel(enemyf, oSphere);
			if(isCollidingModelSphere == true){
				lives--;
				dropSphere();
				delete enemyf;
				enemyf = NULL;
			}
		}
		//Camera
		//if(pLevel1){
			toX = pLevel1->getPos().x; toY = pLevel1->getPos().y; toZ = pLevel1->getPos().z;
		//}
	}
}

void Game::RenderHUD(){
	Set2D(0, m_width, m_height, 0); // Change to 2D view and use 1:1 pixel resolution with [0,0] origin being at the top-left corner.
	glDisable(GL_DEPTH_TEST);  // Disable depth testing so the HUD will not be hidden by the 3D graphics
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);  // Semi-transparent background 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0.0f, 0.0f, 0.9f, 0.5f);
	glBegin(GL_QUADS);
		glVertex2f(0,0);	//top of screen
		glVertex2f(0,20);
		glVertex2f(m_width, 20);
		glVertex2f(m_width, 0);
	glEnd();
	glDisable(GL_BLEND);
	strcpy_s(text, "Ball Dropper - Project Portfolio");
	font1->printString(4, 15, text);
	font1->setColor(1.0f, 1.0f, 0.0f);
	if(GAMESTATE == MAINSTATESCREEN){
		sprintf(text, "Ball Density: %i", (int)sphereDensity);
		font1->printString(400, 50, text);
	}
	if(GAMESTATE == PLAYSTATESCREEN){
		sprintf(text, "Avg FPS: %.1f Score: %i Lives: %i", (float)fCount / cft, (int)score, (int)lives);
		font1->printString(400, 15, text);
		loadFileof.open("loadText.txt");
		char words[225];
		string textScore = "Score: ";
		string result;
		sprintf(words, "%i ", (int)score);
		result = textScore + words;
		loadFileof << result;
	
		//sprintf(text, "Level type: %s Score: %i",);
	}
	if(GAMESTATE == ENDSTATESCREEN){
		getline(loadFileif,line);
		char s[255];
		strcpy(s, line.c_str());
		sprintf(text, "%s", s);
		font1->printString(400, 50, text);
	}
	if(gameState == 0){
	}

	Set3D(VIEW_ANGLE, NEAR_CLIPPING, FAR_CLIPPING); // Set back to 3D
	glEnable(GL_LIGHTING);
}

// Render the objects in their current state.
void Game::Render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Light
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glColor3f(1.0f, 1.0f, 0.0f);
	glPushMatrix();
		glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
//		gluSphere(lSphere, 20.0f, 20, 12);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	if(GAMESTATE == MAINSTATESCREEN){

	}
	if(GAMESTATE == PLAYSTATESCREEN){
		//Camera
		if(placingWalls == false){
			gluLookAt(camX+2, camY+5, camZ, toX, toY, toZ, 0.0f, 1.0f, 0.0f);
		}

		if(placingWalls == true){
			gluLookAt(camX, camY+5, camZ, toX, toY, toZ, 0.0f, 1.0f, 0.0f);
		}
		if(oLevel1){
			oLevel1->render();
		}
		if(goal){
			goal->render();
		}
		//Objects Rendering
		if(oSphere){
			oSphere->render();
		}
		skyBox->render();
		if(enemyf){
			enemyf->output();
		}
	}
	//End
	RenderHUD();
	fCount++;
}

void Game::CameraPos(){
	if(placingWalls == false){
		angNS = ((mouseY + 1) / m_height) * (float)M_PI;  // Map the mouse position to two angles
		angEW = (mouseX / m_width) * 2 * (float)M_PI;
	
		float sinNS = sin(angNS);  // Calculate the sines and cosines of these angles
		float cosNS = cos(angNS);
		float sinEW = sin(angEW);
		float cosEW = cos(angEW);
	
		camZ = camRad * sinNS * cosEW;  // calculate the camera coordinate
		camY = camRad * cosNS;
		camX= camRad * sinNS * sinEW;
	}
}

void Game::initPhysicsObjects(){
	//IMPLEMENTATION OF WORLD
#ifdef _DEBUG
	hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initChecking( hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo(2*1024*1024) );
#else
	hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initDefault( hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo(1024*1024) );
#endif
	hkBaseSystem::init( memoryRouter, errorReport);
	hkpWorldCinfo worldInfo;	// Create the simulation world1
	worldInfo.m_gravity.set(0.0f,-9.8f,0.0f);
	worldInfo.setBroadPhaseWorldSize(100.0f);	//
	m_world = new hkpWorld(worldInfo); 
	m_world->lock();	//****
	// This is needed to detect collisionss
	hkpAgentRegisterUtil::registerAllAgents(m_world->getCollisionDispatcher());
#ifdef _DEBUG
	m_physicsContext = new hkpPhysicsContext();//Connect VDB
	m_physicsContext->addWorld(m_world); // add all worlds
	hkpPhysicsContext::registerAllPhysicsProcesses();
	hkArray<hkProcessContext*> contexts;
	contexts.pushBack(m_physicsContext );  
	m_vdb = new hkVisualDebugger( contexts );
	m_vdb->serve();
#endif
	intCalled = true;
	
	//OBJECTS
	//Make Level1
	createLevel1();
	//Make Sphere and drop it
	pSphere = Sphere::getInstance(sphereDensity);
	pSphere->setPos(Vector(0.0,3.0,0.0));
	pSphere->init(m_world);
	dropSphere();

	//makeWall();

	//Constraints

	//END
	m_world->unlock();
}

void Game::makeWall(){

}

void Game::makeGoal(){
	float randX = rnd.number(-1.0f,1.0f);
	float randZ= rnd.number(-1.0f,1.0f);
	score++;
	goal = new Marker(0.2,0.2,0.2,"Images/goldfoil.bmp");
	goal->setPos(randX, pLevel1->getPos().y + 0.2, randZ);
	goal->setRGB(1.0,1.0,1.0);
}

void Game::deleteEverything(){
	delete goal;
	goal = NULL;
}

void Game::createLevel1(){
	int randType = rnd.number(0, 3);
	if(!pLevel1){
		pLevel1 = levelFact->createLevel(randType,2.0,0.3,2.0, m_world);
		pLevel1->setPos(Vector(0.0,0.0,0.0));

	}
	tiltX = 0;
	tiltZ = 0;
	//pLevel1->initFixed(m_world);
	pLevel1->getRigidBody()->setPosition(hkVector4(0.0,0.0,0.0));
	//droppingY = droppingY - 5.0;

	if(!oLevel1){
		oLevel1 = new OGL_Level(pLevel1, pLevel1->getTextureName());
		oLevel1->setRGB(1.0,1.0,1.0);
	}
}

void Game::deleteLevel1(){
	pLevel1->removeRigidBody(m_world);
	delete pLevel1;
	pLevel1 = NULL;
	delete oLevel1;
	oLevel1 = NULL;
}

void Game::rotatePlatformXAxisPositive(){
//	hkQuaternion* quat = pLevel1->getRigidBody()->getRotation().getAngle;
	pLevel1->getRigidBody()->setRotation(hkQuaternion(0.9990482215818578, 0, 0, 0.04361938736533599));
	
}

void Game::rotatePlatformXAxisNegative(){
//	hkQuaternion* quat = pLevel1->getRigidBody()->getRotation().getAngle;
	pLevel1->getRigidBody()->setRotation(hkQuaternion(0.9990482215818578, 0, 0,-0.04361938736533599));
}

void Game::rotatePlatformZAxisPositive(){
//	hkQuaternion* quat = pLevel1->getRigidBody()->getRotation().getAngle;
	pLevel1->getRigidBody()->setRotation(hkQuaternion(0.9990482215818578, 0.04361938736533599, 0,0));
}

void Game::rotatePlatformZAxisNegative(){
//	hkQuaternion* quat = pLevel1->getRigidBody()->getRotation().getAngle;
	pLevel1->getRigidBody()->setRotation(hkQuaternion(0.9990482215818578, -0.04361938736533599, 0,0));
}

void Game::rotatePlatformXZAxisPositive(){
	pLevel1->getRigidBody()->setRotation(hkQuaternion(0.9980973490458728, 0.04357787137382908, 0.0019026509541272335, 0.04357787137382908));
}

void Game::rotatePlatformXZAxisNegative(){
	pLevel1->getRigidBody()->setRotation(hkQuaternion(0.9980973490458728, -0.04357787137382908, 0.0019026509541272335, -0.04357787137382908));
}

void Game::rotatePlatformXPostiveZNegative(){
	pLevel1->getRigidBody()->setRotation(hkQuaternion(0.9980973490458728, -0.04357787137382908, -0.0019026509541272335, 0.04357787137382908));
}

void Game::rotatePlatformZPostiveXNegative(){
	pLevel1->getRigidBody()->setRotation(hkQuaternion(0.9980973490458728, 0.04357787137382908, -0.0019026509541272335, -0.04357787137382908));
}

void Game::rotatePlatformXZZero(){
	pLevel1->getRigidBody()->setRotation(hkQuaternion(1, 0, 0, 0));
}

void Game::controlsLogic(){
	if(tiltX == 0 && tiltZ == 0){
		rotatePlatformXZZero();
	}
	if(tiltX == 1 && tiltZ == 0){
		rotatePlatformXAxisPositive();
	}
	if(tiltX == -1 && tiltZ == 0){
		rotatePlatformXAxisNegative();
	}
	if(tiltX == 0 && tiltZ == 1){
		rotatePlatformZAxisPositive();
	}
	if(tiltX == 0 && tiltZ == -1){
		rotatePlatformZAxisNegative();
	}
	if(tiltX == 1 && tiltZ == 1){
		rotatePlatformXZAxisPositive();
	}
	if(tiltX == -1 && tiltZ == -1){
		rotatePlatformXZAxisNegative();
	}
	if(tiltX == 1 && tiltZ == -1){
		rotatePlatformXPostiveZNegative();
	}
	if(tiltX == -1 && tiltZ == 1){
		rotatePlatformZPostiveXNegative();
	}
}

void Game::dropSphere(){
	pSphere->getRigidBody()->setPosition(hkVector4(pLevel1->getPos().x+0.1,pLevel1->getPos().y + 3.0,pLevel1->getPos().z));
	pSphere->getRigidBody()->setRotation(hkQuaternion(1,0,0,0));
	pSphere->getRigidBody()->setAngularVelocity(hkVector4(0,0,0));
	pSphere->getRigidBody()->setLinearVelocity(hkVector4(0,0,0));
}

void Game::setSphereDensity(int densityNum){
	sphereDensity = densityNum;
}

int Game::getSphereDensity(){
	return sphereDensity;
}

void Game::playInit(){
	levelFact = new LevelFactoryImplementation();
	enemyFact = new EnemyFactoryImplementation();

	initPhysicsObjects();
	
	oSphere = new OGL_Sphere(pSphere, "Images/metal.bmp");
	oSphere->setRGB(1.0,1.0,1.0);

	skyBox = new Marker(15, 15, 15, "Images/sky.bmp");
	skyBox->setRGB(1.0,1.0,1.0);

	makeGoal();

	loadFileif.open("loadText.txt");
	
	enemyf = enemyFact->createEnemy(SMALL, 100, 60, 10);
}