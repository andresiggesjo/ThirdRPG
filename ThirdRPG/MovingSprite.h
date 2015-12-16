#pragma once
#include "sprite.h"
#include "SDL_Setup.h"
class CMovingSprite :
	public CSprite
{
public:
	CMovingSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY);
	
	~CMovingSprite(void);



	double GetDistance(int X1, int Y1, int X2, int Y2);
	void updateAnimations();
	void updateControls();
	void update();
	void DDraw();
	void handleMouse();
	void setMouseFollow(bool cond);

	//void Draw(); //overrides sprite draw




private:
	bool mouseFollow;
	int *MouseX;
	int *MouseY;
	CSDL_Setup* csdl_setup;

	int timeCheck;
	int animationDelay;

	bool Follow;
	int Follow_Point_X;
	int Follow_Point_Y;

	float distance;
	bool stopAnimation;
};

