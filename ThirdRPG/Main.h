

#pragma once
#include "SDL_Setup.h"
#include "EnvironmentSprite.h"
#include "Sprite.h"
#include <math.h> 
#include "MainCharacter.h"
#include "MovingSprite.h"
#include "Enemy.h"
#include "Border.h"
#include <vector>

class CMain
{
public:
	CMain(int passed_ScreenWidth, int passed_ScreenHeight, CSDL_Setup* passed_SDL_Setup, int* passed_MouseX, int* passed_MouseY);
	~CMain(void);
	void GameLoop();
	void addMouseMovement(CMovingSprite* objtocontrol);
	void addPlayer(CMovingSprite* player);
	void addEnemy(CEnemy* enemy);
	void addBorders(CEnvironmentSprite* border1, CEnvironmentSprite* border2, CEnvironmentSprite* border3, CEnvironmentSprite* border4);
	void addBackground(CEnvironmentSprite* background);
	void cleanup();
	int getMouseX(){ return *MouseX; }
	int getMouseY(){ return *MouseY; }
	std::vector<CSprite*> getObjects();

private:
	int ScreenWidth;
	int ScreenHeight;


	bool quit;


	std::vector<CSprite*> gameEntities;

	
	CSDL_Setup* csdl_setup;

	int *MouseX;
	int *MouseY;
	


};