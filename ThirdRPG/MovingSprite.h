#pragma once
#include "sprite.h"
#include "SDL_Setup.h"
class CMovingSprite :
	public CSprite
{
public:
	CMovingSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup);
	
	~CMovingSprite(void);

	void mouseDown(const SDL_Event&) {}
	void mouseUp(const SDL_Event&) {}
	void keyDown(const SDL_Event&) {}
	void keyUp(const SDL_Event&) {}

	static CMovingSprite* getInstance(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup);

	double getDistance(int X1, int Y1, int X2, int Y2);

	void updateAnimations();
	void update();
	void move();





private:
	

	CSDL_Setup* csdl_setup;

	int timeCheck;
	int animationDelay;
	int follow_Point_X;
	int follow_Point_Y;

	float distance;
	
	bool follow;
	bool stopAnimation;
};

