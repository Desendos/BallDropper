#pragma once
#include "BaseGame.h"
#include "DebugPrint.h"
#include <string>
#include "BFont.h"
#include "Timer.h"
#include "HavokInit.h"

#include <irrKlang.h>

using namespace timer;

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "random.h"
using namespace random;
using namespace std;

const float VIEW_ANGLE = 50.0f; // field of view in the Y direction
const float NEAR_CLIPPING = 0.05f; // near clipping distance (5cm)
const float FAR_CLIPPING = 1000.0f; // far clipping distance (10m)
const int ARRAY_BOX_NUMBER = 4;
const int ARRAY_WALL_NUMBER = 3;

//MY CLASSES
#include "Platform.h"
#include "Box.h"
#include "OGL_Box.h"
#include "Sphere.h"
#include "OGL_Sphere.h"
#include "Marker.h"
#include "LevelFactory.h"
#include "LevelFactoryImplementation.h"
#include "OGL_Level.h"
#include "LevelNormal.h"
#include "Enemy.h"
#include "EnemyFactory.h"
#include "EnemyFactoryImplementation.h"
using namespace irrklang;

const float ANGLE_LIMIT = 5.0f * HK_REAL_PI/180.0f; // 7 degrees limit

/**
The class inherits from BaseGame and provides the game data model and the game logic
*/
class Game : public BaseGame{
	// Allow event handler direct access to these attributes
	// (copied from BaseGame since friendship is not inherited)
	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	// HERE WE DECLARE ANY FONTS, TIMERS OR OTHER VARIABLES WE WANT
	int mouseX, mouseY;
	float camX, camY, camZ, camRad;
	float angEW, angNS;

	BFont* font1;
	char text[256];
	ISoundEngine* m_sEngine;
	Timer* timer;
	float cft, lft, tbf, fps, avgFps;
	unsigned int fCount;
	// HERE WE DECLARE ANY GAME OBJECTS AND CREATE THEM IN THE INITIALISE function

	//HAVOK
	hkpWorld* m_world;		// Havok persistent objects
	#ifdef _DEBUG
		hkVisualDebugger* m_vdb;
		hkpPhysicsContext* m_physicsContext;
	#endif
	///////

	//Physics objects
	LevelFactory* levelFact;
	Level* pLevel1;
	Sphere* pSphere;
	//OpenGL objects
	OGL_Level* oLevel1;
	OGL_Sphere* oSphere;
	Marker* goal;
	Marker* skyBox;
	EnemyFactory* enemyFact;
	Enemy* enemyf;

	//Files
	ofstream loadFileof;
	ifstream loadFileif;

	//Variables
	bool isColliding;
	bool intCalled;
	float toX,toY,toZ;
	bool placingWalls;
	int wallNumber;
	int score;
	float droppingY;
	int tiltX;
	int tiltZ;
	bool sphereInZone;
	int lives;
	string line;
public:
	bool physicsState;
	int gameState;
	Game(void);
	virtual ~Game(void);

	/**
	Use this method to perform any first time initialisation of OpenGL
	*/
	void InitOpenGL();

	/**
	Use this method to create timers, fonts and all game objects. Do NOT 
	execute any OpenGL commands in this method, use initOpenGL instead.
	*/
	void Initialise();

	/**
	Use this method to perform any clean up of objects created for 
	the game - including fonts and timers.
	*/
	void Shutdown();

	/**
	Use this method to create any game objects and initialise the
	game's state
	*/
	bool InitGame();

	/**
	Use this method to update the game's state, but do not use it for rendering
	*/
	void Game::Update();

	/**
	The main rendering method - renders a single frame
	*/
	void Game::Render();

	/**
	Used to alter Camera x, y and z positions
	*/
	void CameraPos();

	/**
	Used to display text messages in game display area
	*/
	void RenderHUD();

	void initPhysicsObjects();
	void makeWall();

	void makeGoal();

	void deleteEverything();

	void createLevel1();
	void deleteLevel1();

	void rotatePlatformXAxisPositive();
	void rotatePlatformXAxisNegative();
	
	void rotatePlatformZAxisPositive();
	void rotatePlatformZAxisNegative();

	void rotatePlatformXZAxisPositive();
	void rotatePlatformXZAxisNegative();

	void rotatePlatformXPostiveZNegative();
	void rotatePlatformZPostiveXNegative();

	void rotatePlatformXZZero();

	void controlsLogic();
	
	void dropSphere();
};
