#include "StdAfx.h"
#include "MainCharacter.h"
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

CMainCharacter::CMainCharacter(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY)
	:  CMovingSprite(passed_renderer, FilePath, x, y , w, h, passed_CollisionRect, passed_SDL_Setup, passed_MouseX, passed_MouseY)

	
{
	csdl_setup = passed_SDL_Setup;
	MouseX = passed_MouseX;
	MouseY = passed_MouseY;
	shouldColl = true;
	health = 200;

	create = true;
	healthbar = new CSprite(csdl_setup->GetRenderer(), "data/health.png", 75,675,130,30, CCollisionRectangle(0,0,0,0)); 


	SetUpAnimation(4,4);
	SetOrgin(GetWidth()/2.0f, GetHeight());
	bulletcheck = SDL_GetTicks();

	timeCheck = SDL_GetTicks();
	Follow = false;
	firebullet = false;
	distance = 0;
	bullet_distance = 0;
	stopAnimation = false;

}


CMainCharacter::~CMainCharacter(void)
{


	delete healthbar;

}

double CMainCharacter::GetDistance(int X1, int Y1, int X2, int Y2)
{
	double DifferenceX = X1 - X2;
	double DifferenceY = Y1 - Y2;
	double distance = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
	return distance;
}

void CMainCharacter::Draw()
{

	if(health == 0 || health < 0)
	{

	}
	else
	{
		//Draw();
		CMovingSprite::Draw();
		healthbar->SetWidth(health);
		healthbar->Draw();
		fire();
		if(firebullet)
		{
			bullet->Draw();
		}


	}

}
void CMainCharacter::updateAnimations()
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
void CMainCharacter::updateControls()
{


	if (csdl_setup->GetMainEvent()->type == SDL_MOUSEBUTTONDOWN || csdl_setup->GetMainEvent()->type == SDL_MOUSEMOTION)
	{
		if (csdl_setup->GetMainEvent()->button.button == SDL_BUTTON_LEFT)
		{
			Follow_Point_X = *MouseX;
			Follow_Point_Y = *MouseY;

			Follow = true;
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
		{
			Follow = false;
		}
		timeCheck = SDL_GetTicks();
	}
}

void CMainCharacter::update()
{

	updateAnimations();
	updateControls();

}

CSprite* CMainCharacter::getHealthbar()
{
	return healthbar;
}
void CMainCharacter::fire()
{

	if (csdl_setup->GetMainEvent()->type == SDL_KEYDOWN)
	{ 

		
		if (csdl_setup->GetMainEvent()->key.keysym.sym)
		{
			if (SDLK_SPACE)
			{
				switch (csdl_setup->GetMainEvent()->key.keysym.sym)
				{
				case SDLK_SPACE:
				
					if(create)
					{
					bullet = new CSprite(csdl_setup->GetRenderer(), "data/fireball_1.png", GetX(),GetY(),100,120, CCollisionRectangle(0,50,75,75)); 
					bullet->SetUpAnimation(8,8);
					bullet->SetOrgin(bullet->GetWidth()/2.0f, bullet->GetHeight());
					firebullet = true;

					bobcurrentx = GetX();
					bobcurrenty = GetY();
					anglez = atan2(Follow_Point_Y - GetY(), Follow_Point_X - GetX());
					anglez = (anglez * (180/3.14)) + 180;
					create = false;
					}
					
					break;

				default:
					break;
				}


			}

		}
		//}
	}


	if(firebullet)
	{


		if (anglez > 45 && anglez <= 135)
		{
			bullet->PlayAnimation(0,7,2,200);
			Bullet_Follow_X = bobcurrentx + 200;
			Bullet_Follow_Y = bobcurrenty - 450;
			bullet_distance = GetDistance(bullet->GetX(), bullet->GetY(), Bullet_Follow_X, Bullet_Follow_Y);

			//up
			if (bullet_distance > 215)
			{
				if (bullet->GetY() != Bullet_Follow_Y)
				{

					bullet->SetY( bullet->GetY() -  ((bullet->GetY()-Bullet_Follow_Y)/bullet_distance) * 1.09f  );
				}

			}
			else
			{
				firebullet = false;
				delete bullet;
				create = true;
			}

			
		}
		else if (anglez > 135 && anglez <= 225)
		{
			bullet->PlayAnimation(0,7,4,200);
			Bullet_Follow_X = bobcurrentx + 450;
			Bullet_Follow_Y = bobcurrenty - 200;
			bullet_distance = GetDistance(bullet->GetX(), bullet->GetY(), Bullet_Follow_X, Bullet_Follow_Y);

			//right
			if (bullet_distance > 215)
			{
				if (bullet->GetX() != Bullet_Follow_X)
				{

					bullet->SetX( bullet->GetX() -  ((bullet->GetX()-Bullet_Follow_X)/bullet_distance) *  1.09f  );

				}

			}
			else
			{
				firebullet = false;
				delete bullet;
				create = true;
			}



		}
		else if (anglez > 225 && anglez <= 315)
		{
			bullet->PlayAnimation(0,7,6,200);
			Bullet_Follow_X = bobcurrentx - 200;
			Bullet_Follow_Y = bobcurrenty + 450;
			bullet_distance = GetDistance(bullet->GetX(), bullet->GetY(), Bullet_Follow_X, Bullet_Follow_Y);

			//down
			if (bullet_distance > 215)
			{
				if (bullet->GetY() != Bullet_Follow_Y)
				{

					bullet->SetY( bullet->GetY() -  ((bullet->GetY()-Bullet_Follow_Y)/bullet_distance) *  1.09f  );

				}

			}
			else
			{
				firebullet = false;
				delete bullet;
				create = true;
			}



		}
		else if ((anglez <= 360 && anglez > 315) || (anglez >=0 && anglez <= 45))
		{
			bullet->PlayAnimation(0,7,0,200);
			Bullet_Follow_X = bobcurrentx - 450;
			Bullet_Follow_Y = bobcurrenty - 200;
			bullet_distance = GetDistance(bullet->GetX(), bullet->GetY(), Bullet_Follow_X, Bullet_Follow_Y);

			//left
			if (bullet_distance > 215)
			{
				if (bullet->GetX() != Bullet_Follow_X)
				{

					bullet->SetX( bullet->GetX() -  ((bullet->GetX()-Bullet_Follow_X)/bullet_distance) *  1.09f  );

				}

			}
			else
			{
				firebullet = false;
				delete bullet;
				create = true;
			}


		}


	}

}
CSprite* CMainCharacter::getBullet()
{
	return bullet;
}
bool CMainCharacter::getFirebullet()
{
	return firebullet;
}
CMovingSprite* CMainCharacter::getBob()
{

	return this;
}
bool CMainCharacter::shouldCollideWith(CSprite* sprite)
{

	if(CEnemy* temp = dynamic_cast<CEnemy*>(sprite))
	{
		return true;
	}
	if(CEnvironmentSprite* temp = dynamic_cast<CEnvironmentSprite*>(sprite))
	{
		return true;
	}

  
  return false;
	
}
bool CMainCharacter::shouldCollide()
{
	return shouldColl;
}