

#pragma once
#include "SDL_Setup.h"
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
	CMain(int passed_ScreenWidth, int passed_ScreenHeight, CSDL_Setup* passed_SDL_Setup);
	~CMain(void);
	void GameLoop();
	void addPlayer(CMovingSprite* player);
	void addEnemy(CEnemy* enemy);
	void addBorders(CSprite* border1, CSprite* border2, CSprite* border3, CSprite* border4);
	void addBackground(CSprite* background);
	void cleanup();

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

	int MouseX;
	int MouseY;
	


};