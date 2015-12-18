#include "StdAfx.h"
#include "Enemy.h"
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG





CEnemy::CEnemy(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup, CMainCharacter* passed_mc)
	: CMovingSprite(passed_renderer, FilePath, x, y, w, h, passed_CollisionRect, passed_SDL_Setup)
{


	mc = passed_mc;
	health = 100;


	csdl_setup = passed_SDL_Setup;

	setUpAnimation(4,4);
	setOrgin(getWidth()/2.0f, getHeight());



	timeCheck = SDL_GetTicks();
	follow = false;
	distance = 0;
	stopAnimation = false;
}


CEnemy::~CEnemy(void)
{
	
}

void CEnemy::draw()
{
	if(health == 0 || health < 0)
	{

	}
	else
	{
	CMovingSprite::draw();
	}
}
void CEnemy::updateAnimations()
{


	float angle = atan2(follow_Point_Y - getY(), follow_Point_X - getX());
	angle = (angle * (180/3.14)) + 180;

	if (!stopAnimation)
	{
		if (angle > 45 && angle <= 135)
		{
			//up

			if (distance > 15)
				playAnimation(0,3,3,200);
			else
				playAnimation(1,1,3,200);
		}
		else if (angle > 135 && angle <= 225)
		{
			//right
			if (distance > 15)
				playAnimation(0,3,2,200);
			else
				playAnimation(1,1,2,200);
		}
		else if (angle > 225 && angle <= 315)
		{
			//down
			if (distance > 15)
				playAnimation(0,3,0,200);
			else
				playAnimation(1,1,0,200);
		}
		else if ((angle <= 360 && angle > 315) || (angle >=0 && angle <= 45))
		{
			//left
			if (distance > 20)
				playAnimation(0,3,1,200);
			else
				playAnimation(1,1,1,200);
		}
	}

}

void CEnemy::updateControls()
{

	if(mc->getHealth() > 0)
	{

		follow_Point_X = mc->getBob()->getX();
		follow_Point_Y = mc->getBob()->getY();
		follow = true;

		if (timeCheck+10 < SDL_GetTicks() && follow)
		{


			
			if(mc->getFirebullet() == true)
 			{
 				if(isColliding(mc->getBullet()->getCollisionRect()))
				{
 					health = health - 25;
					mc->deleteBullet();
 				}
 			}
			

			distance = getDistance(getX(), getY(), follow_Point_X, follow_Point_Y);

			if (distance == 0)
				stopAnimation = true;
			else
				stopAnimation = false;


			if (distance > 15)
			{
				if (getX() != follow_Point_X)
				{
					setX( getX() -  ((getX()-follow_Point_X)/distance) * 0.5f );
				}

				if (getY() != follow_Point_Y)
				{
					setY( getY() -  ((getY()-follow_Point_Y)/distance) * 0.5f );
				}
			}
			else
				follow = false;

			timeCheck = SDL_GetTicks();
		}
	}

}


void CEnemy::update()
{
	updateAnimations();
	updateControls();
}






bool CEnemy::isDead()
{
	if(health < 0 || health == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}





CEnemy* CEnemy::getInstance(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup, CMainCharacter* mc)
{
		return new CEnemy(passed_renderer, FilePath, x, y, w, h, passed_CollisionRect,passed_SDL_Setup, mc);
}