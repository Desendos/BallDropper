#include "Game.h"


Game::Game(void){
	mouseX = mouseY = 0;
	camX = 0.0f;
	camY = 1.0f;
	camZ = camRad = 1.0f;
	fCount = 0;
}

Game::~Game(void){
}

void Game::InitOpenGL(){
	DebugOut("Game::InitOpenGL being called");
	Set2D();
	
}

void Game::Initialise(){
	guiState = MAINSTATE;
	DebugOut("Game::Initialise being called");
	glEnable(GL_POLYGON_SMOOTH);  //set best smoothing
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	timer = new Timer();
	font1 = new BFont(hDC, "Courier", 14);
	gameState =  false;
	if(pForm == NULL && pbox == NULL && pSphere == NULL){
		initPhysicsObjects();
	}
	oPlatform = new OGL_Box(pForm);
	oPlatform->setRGB(1.0f, 0.5f, 0.5f);
	oBox = new OGL_Box(pbox);
	oBox->setRGB(0.0f, 0.0f, 1.0f);
	oSphere = new OGL_Sphere(pSphere);
	oSphere->setRGB(1.0f, 0.0f, 0.0f);
	
}

void Game::Shutdown(){
	DebugOut("Game::Shutdown being called");
	delete timer;
	delete font1;
	//delete pForm;
	//delete pbox;
	//delete pSphere;
	delete oPlatform;
	delete oBox;
	delete oSphere;
}

void Game::Update(){
	cft = timer->getElapsedTime();
	tbf = cft - lft;
	lft = cft;
	if(guiState == MAINSTATE){
		
	}

	if(guiState == GAMESTATE){
		if(gameState){
			m_world->stepDeltaTime(tbf); //update physics engine
			#ifdef _DEBUG
				m_vdb->step(tbf);	// update VDB when running
			#endif
		}
		if(oPlatform){
			oPlatform->update();
		}
		if(oBox){
			oBox->update();
		}

		//oSphere->update();
		//if(oSphere->getHavokObj()->getPos().y < -15.0)//to stop error
		//	gameState = false;
	}
	



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
	strcpy_s(text, "Ball Dropper");
	font1->printString(4, 15, text);
	sprintf(text, "Avg FPS: %.1f", (float)fCount / cft);
	font1->printString(400, 15, text);

	Set3D(VIEW_ANGLE, NEAR_CLIPPING, FAR_CLIPPING); // Set back to 3D
}

void Game::renderMainMenu(){
	Set2D(0, m_width, m_height, 0); // Change to 2D view and use 1:1 pixel resolution with [0,0] origin being at the top-left corner.
	glDisable(GL_DEPTH_TEST);  // Disable depth testing so the HUD will not be hidden by the 3D graphics
	glEnable(GL_BLEND);  // Semi-transparent background 
	
	font1->setColor(1.0f, 1.0f, 0.0f);
	sprintf(text, "Main Menu");
	font1->printString(m_width/2, m_height/2, text);

	Set3D(VIEW_ANGLE, NEAR_CLIPPING, FAR_CLIPPING); // Set back to 3D
}
void Game::renderEndMenu(){
	Set2D(0, m_width, m_height, 0); // Change to 2D view and use 1:1 pixel resolution with [0,0] origin being at the top-left corner.
	glDisable(GL_DEPTH_TEST);  // Disable depth testing so the HUD will not be hidden by the 3D graphics
	glEnable(GL_BLEND);  // Semi-transparent background 
	
	font1->setColor(1.0f, 1.0f, 0.0f);
	sprintf(text, "Game Over");
	font1->printString(m_width/2, m_height/2, text);

	Set3D(VIEW_ANGLE, NEAR_CLIPPING, FAR_CLIPPING); // Set back to 3D
}

// Render the objects in their current state.
void Game::Render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluLookAt(camX,camY+10,camZ, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	if(guiState == GAMESTATE){
		oPlatform->render();
		oBox->render();
//		oSphere->update();
	}
	if(guiState == MAINSTATE){
		renderMainMenu();	
	}
	if(guiState == ENDSTATE){
		renderEndMenu();	
	}

	RenderHUD();
	fCount++;
}

void Game::CameraPos(){
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

void Game::initPhysicsObjects(){
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
	if(pForm == NULL){
		pForm = new box(2.0f,0.1f,2.0f);
	}
	pForm->setPos(Vector(1.0f, 1.2f, 0.0f));
	pForm->init(m_world);
	if(pbox == NULL){
		pbox = new box;
	}
	pbox->setPos(Vector(1.0f, 1.2f, 0.0f));
	pbox->init(m_world);
	if(pSphere == NULL){
		pSphere =  new Sphere(2.0f,0.1f,2.0f);
	}
	pForm->setPos(Vector(1.2f, 1.2f, 0.0f));
	pSphere->init(m_world);

	hkpGenericConstraintData* data = new hkpGenericConstraintData();	// Create constraint on the level
	hkpConstraintConstructionKit kit;
	kit.begin(data);
		kit.setPivotA(hkVector4(0.0f, 0.0f, 0.0f));	
		kit.setPivotB(hkVector4(1.0f, 0.0f, 0.0f));
		kit.constrainAllLinearDof();
		kit.setAngularBasisABodyFrame();
		kit.setAngularBasisBBodyFrame();

		kit.setAngularLimit(0, -ANGLE_LIMIT, ANGLE_LIMIT);	
		//// do not limit rotation around Y axis
		kit.setAngularLimit(2, 0.0f, 0.0f);  //stop z-axis rotation
	kit.end();
	hkpConstraintInstance* constraint = new hkpConstraintInstance(pForm->getRigidBody(), NULL, data);
	m_world->addConstraint(constraint);
	data->removeReference();
	constraint->removeReference();

	m_world->unlock();
}

void Game::removeGameObjects(){
	guiState = ENDSTATE;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//delete pForm;
	//delete pbox;
	//delete pSphere;
	delete oPlatform;
	delete oBox;
	//delete oSphere;
}

void Game::createGameObjects(){
	guiState = GAMESTATE;
	gameState =  false;
	initPhysicsObjects();
	if(oPlatform == NULL){
		oPlatform = new OGL_Box(pForm);
	}
	oPlatform->setRGB(1.0f, 0.5f, 0.5f);
	if(oBox == NULL){
		oBox = new OGL_Box(pbox);
	}
	oBox->setRGB(0.0f, 0.0f, 1.0f);
	if(oSphere == NULL){
		oSphere = new OGL_Sphere(pSphere);
	}
	oSphere->setRGB(1.0f, 0.0f, 0.0f);
}