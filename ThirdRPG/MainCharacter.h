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
	CMainCharacter(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup);
	~CMainCharacter(void);


	static CMainCharacter* getInstance(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup);

	void deleteBullet();
	void keyDown(const SDL_Event&);
	void mouseDown(const SDL_Event&);
	void addEnemies(CSprite* comp);
	void addBorders(CSprite* comp);
	void updateFire();
	void fire();
	void updateControls();
	void updateAnimations();
	void update();
	void draw();
	void setHealth(int passed_health){ health = passed_health; }
	void collidingEffter();

	int getHealth(){ return health; }
	

	CMovingSprite* getBob();
	CSprite* getBullet();
	CSprite* getHealthbar();

	bool getFirebullet();




private:

	CSDL_Setup* csdl_setup;

	std::vector<CSprite*> borders;
	std::vector<CSprite*> enemies;

	CSprite* healthbar;
	CSprite* bullet;
	
	float anglez;
	float distance;
	float bullet_distance;

	int health;
	int bobcurrentx;
	int bobcurrenty;
	int follow_Point_X;
	int follow_Point_Y;
	int bullet_Follow_X;
	int bullet_Follow_Y;
	int timeCheck;
	int bulletcheck;
	int animationDelay;

	bool follow;
	bool firebullet;
	bool stopAnimation;
	bool create;

};

