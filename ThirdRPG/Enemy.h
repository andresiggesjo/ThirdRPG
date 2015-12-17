#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"
#include "EnvironmentSprite.h"
#include "MainCharacter.h"
#include "MovingSprite.h"
#include <vector>

#include <math.h>

class CEnemy : 
	public CMovingSprite
{
public:
	CEnemy(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, CMainCharacter* mc);
	~CEnemy(void);

	static CEnemy* getInstance(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, CMainCharacter* mc);

	void setMainchar();
	double GetDistance(int X1, int Y1, int X2, int Y2);
	int getHealth(){ return health;}
	void update();
	void UpdateControls();
	void Draw();
	bool isDead();
	bool shouldCollideWith(CSprite* sprite);
	bool shouldCollide();

private:
	

	void UpdateAnimation();
	bool shouldColl;
	CMainCharacter* mc;
	std::vector<CSprite*> gameObjects;
	CSDL_Setup* csdl_setup;


	int timeCheck;
	int health;
	bool Follow;
	int Follow_Point_X;
	int Follow_Point_Y;

	float distance;
	bool stopAnimation;
};

