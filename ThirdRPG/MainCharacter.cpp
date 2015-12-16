#include "StdAfx.h"
#include "MainCharacter.h"
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

CMainCharacter::CMainCharacter(CSDL_Setup* passed_SDL_Setup, int *passed_MouseX, int *passed_MouseY,std::vector<CSprite*> passed_borders)
{
	csdl_setup = passed_SDL_Setup;
	MouseX = passed_MouseX;
	MouseY = passed_MouseY;
	borders = passed_borders;
	health = 200;

	create = true;
	bob = new CSprite(csdl_setup->GetRenderer(),"data/mainchar.png", 300,250, 100,120, CCollisionRectangle(30,20,50,90));
	healthbar = new CSprite(csdl_setup->GetRenderer(), "data/health.png", 75,675,130,30, CCollisionRectangle(0,0,0,0)); 


	bob->SetUpAnimation(4,4);
	bob->SetOrgin(bob->GetWidth()/2.0f, bob->GetHeight());
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

	delete bob;
	delete healthbar;

}

double CMainCharacter::GetDistance(int X1, int Y1, int X2, int Y2)
{
	double DifferenceX = X1 - X2;
	double DifferenceY = Y1 - Y2;
	double distance = sqrt((DifferenceX * DifferenceX) + (DifferenceY * DifferenceY));
	return distance;
}

void CMainCharacter::draw()
{

	if(health == 0 || health < 0)
	{

	}
	else
	{
		bob->Draw();
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
	float angle = atan2(Follow_Point_Y - bob->GetY(), Follow_Point_X - bob->GetX());
	angle = (angle * (180/3.14)) + 180;

	if (!stopAnimation)
	{
		if (angle > 45 && angle <= 135)
		{
			//up

			if (distance > 15)
				bob->PlayAnimation(0,3,3,200);
			else
				bob->PlayAnimation(1,1,3,200);
		}
		else if (angle > 135 && angle <= 225)
		{
			//right
			if (distance > 15)
				bob->PlayAnimation(0,3,2,200);
			else
				bob->PlayAnimation(1,1,2,200);
		}
		else if (angle > 225 && angle <= 315)
		{
			//down
			if (distance > 15)
				bob->PlayAnimation(0,3,0,200);
			else
				bob->PlayAnimation(1,1,0,200);
		}
		else if ((angle <= 360 && angle > 315) || (angle >=0 && angle <= 45))
		{
			//left
			if (distance > 20)
				bob->PlayAnimation(0,3,1,200);
			else
				bob->PlayAnimation(1,1,1,200);
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

		distance = GetDistance(bob->GetX(), bob->GetY(), Follow_Point_X, Follow_Point_Y);

		if (distance == 0)
			stopAnimation = true;
		else
			stopAnimation = false;

		for(int i = 0; i < borders.size(); i++)
		{
			if(bob->isColliding(borders[i]->GetCollisionRect()))
			{



				if (bob->GetX() > Follow_Point_X)
				{
					//left
					bob->SetX(bob->GetX() + 5);
					setHealth(getHealth() - 5);
					Follow_Point_X = bob->GetX();

				}
				if (bob->GetX() < Follow_Point_X)
				{
					//right
					bob->SetX(bob->GetX() - 5);
					setHealth(getHealth() - 5);
					Follow_Point_X = bob->GetX();

				}

				if (bob->GetY() > Follow_Point_Y)
				{
					//up
					//buggar vid kollision om man inte ändrar followpointsen
					Follow_Point_Y = bob->GetY() - 5;
					bob->SetY(bob->GetY() + 5);
					setHealth(getHealth() - 5);


				}
				if (bob->GetY() < Follow_Point_Y)
				{
					//down
					Follow_Point_Y = bob->GetY() + 5;
					bob->SetY(bob->GetY() - 5);
					setHealth(getHealth() - 5);


				}
			}
		}

		if (distance > 15)
		{
			if (bob->GetX() != Follow_Point_X)
			{
				bob->SetX( bob->GetX() -  ((bob->GetX()-Follow_Point_X)/distance) * 1.5f );
			}

			if (bob->GetY() != Follow_Point_Y)
			{
				bob->SetY( bob->GetY() -  ((bob->GetY()-Follow_Point_Y)/distance) * 1.5f );
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
CSprite* CMainCharacter::getBob()
{
	return bob;
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
					bullet = new CSprite(csdl_setup->GetRenderer(), "data/fireball_1.png", bob->GetX(),bob->GetY(),100,120, CCollisionRectangle(0,50,75,75)); 
					bullet->SetUpAnimation(8,8);
					bullet->SetOrgin(bullet->GetWidth()/2.0f, bullet->GetHeight());
					firebullet = true;

					bobcurrentx = bob->GetX();
					bobcurrenty = bob->GetY();
					anglez = atan2(Follow_Point_Y - bob->GetY(), Follow_Point_X - bob->GetX());
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

					bullet->SetY( bullet->GetY() -  ((bullet->GetY()-Bullet_Follow_Y)/bullet_distance) * 0.09f  );
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

					bullet->SetX( bullet->GetX() -  ((bullet->GetX()-Bullet_Follow_X)/bullet_distance) *  0.09f  );

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

					bullet->SetY( bullet->GetY() -  ((bullet->GetY()-Bullet_Follow_Y)/bullet_distance) *  0.09f  );

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

					bullet->SetX( bullet->GetX() -  ((bullet->GetX()-Bullet_Follow_X)/bullet_distance) *  0.09f  );

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
