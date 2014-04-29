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
}

Game::~Game(void){
	deleteEverything();
	
}

void Game::InitOpenGL(){
	DebugOut("Game::InitOpenGL being called");
	Set2D();
}

void Game::Initialise(){
	DebugOut("Game::Initialise being called");
	glEnable(GL_POLYGON_SMOOTH);  //set best smoothing
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	levelFact = new LevelFactoryImplementation();

	timer = new Timer();
	font1 = new BFont(hDC, "Courier", 14);
	initPhysicsObjects();
	
	oSphere = new OGL_Sphere(pSphere, "Images/green.bmp");
	oSphere->setRGB(0.0,1.0,0.0);

	makeGoal();
}

void Game::Shutdown(){

	DebugOut("Game::Shutdown being called");
	delete timer;
	delete font1;
}

void Game::Update(){
	//Timers
	while(timer->getElapsedTime() - lft - 1.0f/60.0f < 0.001f); //Frame Limiter (set to 60 FPS)
	cft = timer->getElapsedTime();
	tbf = cft - lft;
	lft = cft;
	//Havok
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
	if(goal){
		isColliding = goal->collidesWithSphere(oSphere);
		if(isColliding == true){
			deleteEverything();
			makeGoal();
		}
	}
	//Camera
	//if(pLevel1){
		toX = pLevel1->getPos().x; toY = pLevel1->getPos().y; toZ = pLevel1->getPos().z;
	//}
}

void Game::RenderHUD(){
	Set2D(0, m_width, m_height, 0); // Change to 2D view and use 1:1 pixel resolution with [0,0] origin being at the top-left corner.
	glDisable(GL_DEPTH_TEST);  // Disable depth testing so the HUD will not be hidden by the 3D graphics
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
	
	font1->setColor(1.0f, 1.0f, 0.0f);
	strcpy_s(text, "Ball Droppen - OpenGL and Havok - Project Portfolio");
	font1->printString(4, 15, text);
	sprintf(text, "Avg FPS: %.1f", (float)fCount / cft);
	font1->printString(600, 15, text);
	//sprintf(text, "Level type: %s Score: %i",);
	
	if(gameState == 0){
	}

	Set3D(VIEW_ANGLE, NEAR_CLIPPING, FAR_CLIPPING); // Set back to 3D
}

// Render the objects in their current state.
void Game::Render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Camera
	if(placingWalls == false){
		gluLookAt(camX+2, camY+2 - droppingY, camZ, toX, toY, toZ, 0.0f, 1.0f, 0.0f);
	}

	if(placingWalls == true){
		gluLookAt(camX, camY+10 - droppingY, camZ, toX, toY, toZ, 0.0f, 1.0f, 0.0f);
	}
	if(oLevel1){
		oLevel1->render();
	}
	if(goal){
		goal->render();
	}
	//Objects Rendering
	
	oSphere->render();
	
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

	createLevel1();

	pSphere = new Sphere(0.2,0.2,0.2);
	pSphere->setPos(Vector(0.0,3.0,0.0));
	pSphere->init(m_world);

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
		pLevel1 = levelFact->createLevel(randType,2.0,0.1,2.0);
		pLevel1->setPos(Vector(0.0,0.0,0.0));

	}
	tiltX = 0;
	tiltZ = 0;
	pLevel1->initFixed(m_world);
	pLevel1->getRigidBody()->setPosition(hkVector4(0.0,droppingY,0.0));
	droppingY = droppingY - 5.0;

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
	if(tiltX == 0){
		pLevel1->getRigidBody()->setRotation(hkQuaternion(0.9990482215818578, 0, 0,0.04361938736533599));
		tiltX = 1;
	}
	if(tiltX == -1){
		pLevel1->getRigidBody()->setRotation(hkQuaternion(1, 0, 0, 0));
		tiltX = 0;
	}
}

void Game::rotatePlatformXAxisNegative(){
//	hkQuaternion* quat = pLevel1->getRigidBody()->getRotation().getAngle;
	if(tiltX == 0){
			pLevel1->getRigidBody()->setRotation(hkQuaternion(0.9990482215818578, 0, 0,-0.04361938736533599));
		tiltX = -1;
	}
	if(tiltX == 1){
		pLevel1->getRigidBody()->setRotation(hkQuaternion(1, 0, 0, 0));
		tiltX = 0;
	}
}

void Game::rotatePlatformZAxisPositive(){
//	hkQuaternion* quat = pLevel1->getRigidBody()->getRotation().getAngle;
	if(tiltZ == 0){
		pLevel1->getRigidBody()->setRotation(hkQuaternion(0.9990482215818578, 0.04361938736533599, 0,0));
		tiltZ = 1;
	}
	if(tiltZ == -1){
		pLevel1->getRigidBody()->setRotation(hkQuaternion(1, 0, 0, 0));
		tiltZ = 0;
	}
}

void Game::rotatePlatformZAxisNegative(){
//	hkQuaternion* quat = pLevel1->getRigidBody()->getRotation().getAngle;
	if(tiltZ == 0){
			pLevel1->getRigidBody()->setRotation(hkQuaternion(0.9990482215818578, -0.04361938736533599, 0,0));
		tiltZ = -1;
	}
	if(tiltZ == 1){
		pLevel1->getRigidBody()->setRotation(hkQuaternion(1, 0, 0, 0));
		tiltZ = 0;
	}
}