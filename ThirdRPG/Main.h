

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


private:
	int ScreenWidth;
	int ScreenHeight;


	bool quit;
	
	CMainCharacter* bob;
	CMovingSprite* bobnumerodos;
	CSprite* grass;
	std::vector<CSprite*> borders;
	std::vector<CSprite*> gameEntities;
	int Mode, cc1, cc2, cc3, cc4;

	std::vector<CMainCharacter*> gameObjects;
	std::vector<CEnemy*> gameObjects1;


	
	CEnemy* enemy;
	CEnemy* enemy1;
	
	CSDL_Setup* csdl_setup;

	int *MouseX;
	int *MouseY;
	


};