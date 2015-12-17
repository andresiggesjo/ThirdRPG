#include "StdAfx.h"
#include "MovingSprite.h"
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

CMovingSprite::CMovingSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup)
		: CSprite(passed_renderer, FilePath, x, y , w, h, passed_CollisionRect)
{

	csdl_setup = passed_SDL_Setup;
	


	//spelspeficikt(4,4)
	SetUpAnimation(4,4);
	SetOrgin(GetWidth()/2.0f, GetHeight());


	timeCheck = SDL_GetTicks();
	Follow = false;
	distance = 0;
	stopAnimation = false;
}



CMovingSprite::~CMovingSprite(void)
{
}


void CMovingSprite::update()
{

	updateAnimations();

}
void CMovingSprite::updateAnimations()
{
	//generell move animation
	float angle = atan2(Follow_Point_Y - GetY(), Follow_Point_X - GetX());
	angle = (angle * (180/3.14)) + 180;

	if (!stopAnimation)
	{
		if (angle > 45 && angle <= 135)
		{
			//up

			if (distance > 15)
				PlayAnimation(0,3,3,200);
			else
				PlayAnimation(1,1,3,200);
		}
		else if (angle > 135 && angle <= 225)
		{
			//right
			if (distance > 15)
				PlayAnimation(0,3,2,200);
			else
				PlayAnimation(1,1,2,200);
		}
		else if (angle > 225 && angle <= 315)
		{
			//down
			if (distance > 15)
				PlayAnimation(0,3,0,200);
			else
				PlayAnimation(1,1,0,200);
		}
		else if ((angle <= 360 && angle > 315) || (angle >=0 && angle <= 45))
		{
			//left
			if (distance > 20)
				PlayAnimation(0,3,1,200);
			else
				PlayAnimation(1,1,1,200);
		}
	}

}



double CMovingSprite::GetDistance(int X1, int Y1, int X2, int Y2)
{
	double DifferenceX = X1 - X2;
	double DifferenceY = Y1 - Y2;
	double distance = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
	return distance;
}

CMovingSprite* CMovingSprite::getInstance(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup)
{
		return new CMovingSprite(passed_renderer, FilePath, x, y, w, h, passed_CollisionRect,passed_SDL_Setup);
}