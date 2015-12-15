#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"
#include <math.h>
#include <vector>

class CMainCharacter
{
public:
	CMainCharacter(CSDL_Setup* passed_SDL_Setup, int *MouseX, int *MouseY,std::vector<CSprite*> passed_borders);
	~CMainCharacter(void);

	void cleanup();
	void updateFire();
	void fire();
	void updateAnimations();
	void updateControls();
	void update();
	void draw();
	int getHealth(){ return health; }
	void setHealth(int passed_health){ health = passed_health; }
	CSprite* getBob();
	CSprite* getBullet();
	CSprite* getHealthbar();
	bool getFirebullet();
	void PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed);
	void SetUpAnimation(int passed_Amount_X, int passed_Amount_Y);

	double GetDistance(int X1, int Y1, int X2, int Y2);


private:

	int *MouseX;
	int *MouseY;
	float anglez;
	int health;
	int mana;

	CSDL_Setup* csdl_setup;

	CSprite* bob;
	CSprite* healthbar;
	CSprite* bullet;
	CSprite* manabar;
	std::vector<CSprite*> borders;
	int timeCheck;
	int bulletcheck;


	int animationDelay;

	bool Follow;
	bool firebullet;

	int Follow_Point_X;
	int Follow_Point_Y;
	int Bullet_Follow_X;
	int Bullet_Follow_Y;
	int bobcurrentx;
	int bobcurrenty;

	float distance;
	float bullet_distance;
	bool stopAnimation;

};

