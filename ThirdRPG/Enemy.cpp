#include "StdAfx.h"
#include "Enemy.h"
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG





CEnemy::CEnemy(CSDL_Setup* passed_SDL_Setup, CMainCharacter* passed_mc, int x , int y, std::vector<CSprite*> passed_borders)
{

	//BEHÖVER TA IN PLAYER X OCH PLAYER Y

	mc = passed_mc;
	health = 100;
	borders = passed_borders;

	csdl_setup = passed_SDL_Setup;
	enemy = new CSprite(csdl_setup->GetRenderer(),"data/enemy.png", x,y, 100,100,CCollisionRectangle(25, 0, 50, 100));
	enemy->SetUpAnimation(4,4);
	enemy->SetOrgin(enemy->GetWidth()/2.0f, enemy->GetHeight());



	timeCheck = SDL_GetTicks();
	Follow = false;
	distance = 0;
	stopAnimation = false;
}


CEnemy::~CEnemy(void)
{
	
	delete enemy;
	enemy = NULL;
}

void CEnemy::Draw()
{
	if(health == 0 || health < 0)
	{

	}
	else
	{
	enemy->Draw();
	}
}
void CEnemy::UpdateAnimation()
{
	//rita animationer beroende på movement som beror på spelarens x y
	//ta reda på spelarens x, y och följ efter spelaren 



	float angle = atan2(Follow_Point_Y - enemy->GetY(), Follow_Point_X - enemy->GetX());
	angle = (angle * (180/3.14)) + 180;

	if (!stopAnimation)
	{
		if (angle > 45 && angle <= 135)
		{
			//up

			if (distance > 15)
				enemy->PlayAnimation(0,3,3,200);
			else
				enemy->PlayAnimation(1,1,3,200);
		}
		else if (angle > 135 && angle <= 225)
		{
			//right
			if (distance > 15)
				enemy->PlayAnimation(0,3,2,200);
			else
				enemy->PlayAnimation(1,1,2,200);
		}
		else if (angle > 225 && angle <= 315)
		{
			//down
			if (distance > 15)
				enemy->PlayAnimation(0,3,0,200);
			else
				enemy->PlayAnimation(1,1,0,200);
		}
		else if ((angle <= 360 && angle > 315) || (angle >=0 && angle <= 45))
		{
			//left
			if (distance > 20)
				enemy->PlayAnimation(0,3,1,200);
			else
				enemy->PlayAnimation(1,1,1,200);
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

			if(enemy->isColliding(mc->getBob()->GetCollisionRect()))
			{

				if (enemy->GetX() > Follow_Point_X)
				{
					enemy->SetX(enemy->GetX() + 50);
					mc->setHealth(mc->getHealth() - 40);


				}
				if (enemy->GetX() < Follow_Point_X)
				{
					enemy->SetX(enemy->GetX() - 50);
					mc->setHealth(mc->getHealth() - 40);
				}

				if (enemy->GetY() > Follow_Point_Y)
				{
					enemy->SetY(enemy->GetY() + 50);
					mc->setHealth(mc->getHealth() - 40);
				}
				if (enemy->GetY() < Follow_Point_Y)
				{
					enemy->SetY(enemy->GetY() - 50);
					mc->setHealth(mc->getHealth() - 40);
				}

			}
			for(int i = 0; i < borders.size(); i++)
			{
				if(enemy->isColliding(borders[i]->GetCollisionRect()))
				{
					if (enemy->GetX() > Follow_Point_X)
					{
						enemy->SetX(enemy->GetX() + 1);

					}
					if (enemy->GetX() < Follow_Point_X)
					{
						enemy->SetX(enemy->GetX() - 1);

					}

					if (enemy->GetY() > Follow_Point_Y)
					{
						enemy->SetY(enemy->GetY() + 1);

					}
					if (enemy->GetY() < Follow_Point_Y)
					{
						enemy->SetY(enemy->GetY() - 1);

					}
				}
			}
			if(mc->getFirebullet() == true)
			{
				if(enemy->isColliding(mc->getBullet()->GetCollisionRect()))
				{
					health = 0;
				}
			}


			distance = GetDistance(enemy->GetX(), enemy->GetY(), Follow_Point_X, Follow_Point_Y);

			if (distance == 0)
				stopAnimation = true;
			else
				stopAnimation = false;


			if (distance > 15)
			{
				if (enemy->GetX() != Follow_Point_X)
				{
					enemy->SetX( enemy->GetX() -  ((enemy->GetX()-Follow_Point_X)/distance) * 0.5f );
				}

				if (enemy->GetY() != Follow_Point_Y)
				{
					enemy->SetY( enemy->GetY() -  ((enemy->GetY()-Follow_Point_Y)/distance) * 0.5f );
				}
			}
			else
				Follow = false;

			timeCheck = SDL_GetTicks();
		}
	}

}


void CEnemy::Update()
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