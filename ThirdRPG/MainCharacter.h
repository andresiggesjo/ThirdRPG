#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"
#include "MovingSprite.h"
#include <math.h>
#include <vector>

class CMainCharacter :
	public CMovingSprite
{
public:
	CMainCharacter(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY);
	~CMainCharacter(void);


	static CMainCharacter* getInstance(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY);

	bool shouldCollideWith(CSprite* sprite);
	bool shouldCollide();
	void cleanup();
	void updateFire();
	void fire();
	void updateControls();
	void updateAnimations();
	void update();
	void Draw();
	int getHealth(){ return health; }
	void setHealth(int passed_health){ health = passed_health; }
	CMovingSprite* getBob();
	CSprite* getBullet();
	CSprite* getHealthbar();
	bool getFirebullet();

	double GetDistance(int X1, int Y1, int X2, int Y2);


private:
	bool shouldColl;
	int *MouseX;
	int *MouseY;
	float anglez;
	int health;
	int mana;

	CSDL_Setup* csdl_setup;


	CSprite* healthbar;
	CSprite* bullet;


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
	bool create;

};

