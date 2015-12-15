// Let's Make An RPG - Part 22 - Main.h   www.youtube.com/youkondziu

#pragma once
#include "SDL_Setup.h"
#include "Sprite.h"
#include <math.h> 
#include "MainCharacter.h"
#include "Enemy.h"
#include "Border.h"
#include <vector>

class CMain
{
public:
	CMain(int passed_ScreenWidth, int passed_ScreenHeight);
	~CMain(void);
	void GameLoop();
	void addPlayer(CMainCharacter* player);
	void addEnemy(CEnemy* enemy,CMainCharacter* player, int startx, int starty);
	void addBorders();
	void cleanup();

private:
	int ScreenWidth;
	int ScreenHeight;


	bool quit;
	
	CMainCharacter* bob;

	CSprite* grass;
	std::vector<CSprite*> borders;
	int Mode, cc1, cc2, cc3, cc4;
	//CSprite* platform;
	//CSprite* platform1;
	std::vector<CMainCharacter*> gameObjects;
	std::vector<CEnemy*> gameObjects1;


	
	CEnemy* enemy;
	CEnemy* enemy1;
	
	CSDL_Setup* csdl_setup;

	int MouseX;
	int MouseY;
	


};