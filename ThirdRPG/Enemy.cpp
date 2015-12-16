#include "StdAfx.h"
#include "Enemy.h"
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG





CEnemy::CEnemy(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY, CMainCharacter* passed_mc)
	: CMovingSprite(passed_renderer, FilePath, x, y, w, h, passed_CollisionRect, passed_SDL_Setup, passed_MouseX, passed_MouseY)
{

	//BEHÖVER TA IN PLAYER X OCH PLAYER Y

	mc = passed_mc;
	health = 100;

	shouldColl = true;
	csdl_setup = passed_SDL_Setup;

	SetUpAnimation(4,4);
	SetOrgin(GetWidth()/2.0f, GetHeight());



	timeCheck = SDL_GetTicks();
	Follow = false;
	distance = 0;
	stopAnimation = false;
}


CEnemy::~CEnemy(void)
{
	


}

void CEnemy::Draw()
{
	if(health == 0 || health < 0)
	{

	}
	else
	{
	CMovingSprite::Draw();
	}
}
void CEnemy::UpdateAnimation()
{
	//rita animationer beroende på movement som beror på spelarens x y
	//ta reda på spelarens x, y och följ efter spelaren 



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

void CEnemy::UpdateControls()
{

	if(mc->getHealth() > 0)
	{

		Follow_Point_X = mc->getBob()->GetX();
		Follow_Point_Y = mc->getBob()->GetY();
		Follow = true;

		if (timeCheck+10 < SDL_GetTicks() && Follow)
		{


			for (int i = 0; i < gameObjects.size(); i++)
			{
				if(this->isColliding(gameObjects[i]->GetCollisionRect()))
				{

					std::cout<<"Hääy hääy häääy"<<std::endl;
				}
			
			}

			distance = GetDistance(GetX(), GetY(), Follow_Point_X, Follow_Point_Y);

			if (distance == 0)
				stopAnimation = true;
			else
				stopAnimation = false;


			if (distance > 15)
			{
				if (GetX() != Follow_Point_X)
				{
					SetX( GetX() -  ((GetX()-Follow_Point_X)/distance) * 0.5f );
				}

				if (GetY() != Follow_Point_Y)
				{
					SetY( GetY() -  ((GetY()-Follow_Point_Y)/distance) * 0.5f );
				}
			}
			else
				Follow = false;

			timeCheck = SDL_GetTicks();
		}
	}

}


void CEnemy::update()
{
	UpdateAnimation();
	UpdateControls();
}




double CEnemy::GetDistance(int X1, int Y1, int X2, int Y2)
{
	double DifferenceX = X1 - X2;
	double DifferenceY = Y1 - Y2;
	double distance = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
	return distance;
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
void CEnemy::setMainchar()
{
	mc = nullptr;
}

bool CEnemy::shouldCollideWith(CSprite* sprite)
{

	if(CMainCharacter* temp = dynamic_cast<CMainCharacter*>(sprite))
	{
		return true;
	}
	if(CEnvironmentSprite* temp = dynamic_cast<CEnvironmentSprite*>(sprite))
	{
		return true;
	}

  
  return false;
	
}

bool CEnemy::shouldCollide()
{
	return shouldColl;
}