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
	CEnemy(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup, CMainCharacter* mc);
	~CEnemy(void);

	static CEnemy* getInstance(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup, CMainCharacter* mc);


	
	int getHealth(){ return health;}
	int setHealth(int passed_health){ health = passed_health; }

	void update();
	void updateAnimations();
	void updateControls();
	void draw();

	bool isDead();


private:
	

	

	CMainCharacter* mc;

	CSDL_Setup* csdl_setup;


	int timeCheck;
	int health;
	int follow_Point_X;
	int follow_Point_Y;

	float distance;
	
	bool follow;
	bool stopAnimation;
};

