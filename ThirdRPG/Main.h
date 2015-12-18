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
	CMain(int passed_ScreenWidth, int passed_ScreenHeight, CSDL_Setup* passed_SDL_Setup);
	~CMain(void);


	void add(CSprite* comp);
	void gameLoop();



private:

	int screenWidth;
	int screenHeight;
	bool quit;
	std::vector<CSprite*> gameEntities;
	CSDL_Setup* csdl_setup;


};