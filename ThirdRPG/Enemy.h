#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"
#include "Environment.h"
#include "MainCharacter.h"
#include "MovingSprite.h"
#include <vector>

#include <math.h>

class CEnemy
{
public:
	CEnemy(CSDL_Setup* passed_SDL_Setup, CMovingSprite* mc, int x, int y, std::vector<CSprite*> passed_borders);
	~CEnemy(void);

	void setMainchar();
	double GetDistance(int X1, int Y1, int X2, int Y2);
	int getHealth(){ return health;}
	CSprite* getEnemy() { return enemy; }
	void Update();
	void UpdateControls();
	void Draw();
	bool isDead();

private:
	

	void UpdateAnimation();

	CMovingSprite* mc;

	CSDL_Setup* csdl_setup;
	std::vector<CSprite*> borders;
	CSprite* enemy;
	int timeCheck;
	int health;
	bool Follow;
	int Follow_Point_X;
	int Follow_Point_Y;

	float distance;
	bool stopAnimation;
};

