#include "StdAfx.h"
#include "MovingSprite.h"


CMovingSprite::CMovingSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY)
		: CSprite(passed_renderer, FilePath, x, y , w, h, passed_CollisionRect)
{

	csdl_setup = passed_SDL_Setup;
	//spelspefickt musX å musY
	MouseX = passed_MouseX;
	MouseY = passed_MouseY;

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

void CMovingSprite::Draw()
{
	//Draw();

}

void CMovingSprite::update()
{

	updateAnimations();
	updateControls();

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

void CMovingSprite::handleMouse()
{


}
void CMovingSprite::updateControls()
{

	//spelspecifik movement
	if (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN || csdl_setup->GetMainEvent()->type == SDL_MOUSEMOTION)
	{
		
		if (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
		{
			
			Follow_Point_X = *MouseX;
			Follow_Point_Y = *MouseY;

			Follow = true;
			handleMouse();
		}
	}

	if (timeCheck+10 < SDL_GetTicks() && Follow)
	{

		distance = GetDistance(GetX(), GetY(), Follow_Point_X, Follow_Point_Y);

		if (distance == 0)
			stopAnimation = true;
		else
			stopAnimation = false;

		

			
		

		if (distance > 15)
		{
			if (GetX() != Follow_Point_X)
			{
				SetX( GetX() -  ((GetX()-Follow_Point_X)/distance) * 1.5f );

			}

			if (GetY() != Follow_Point_Y)
			{
				SetY( GetY() -  ((GetY()-Follow_Point_Y)/distance) * 1.5f );
			}
		}
		else
			Follow = false;

		timeCheck = SDL_GetTicks();
	
	}
}

double CMovingSprite::GetDistance(int X1, int Y1, int X2, int Y2)
{
	double DifferenceX = X1 - X2;
	double DifferenceY = Y1 - Y2;
	double distance = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
	return distance;
}

