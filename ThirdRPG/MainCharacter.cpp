#include "StdAfx.h"
#include "MainCharacter.h"
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

CMainCharacter::CMainCharacter(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup)
	:  CMovingSprite(passed_renderer, FilePath, x, y , w, h, passed_CollisionRect, passed_SDL_Setup)


{
	csdl_setup = passed_SDL_Setup;


	health = 200;

	create = true;
	healthbar = new CSprite(csdl_setup->getRenderer(), "data/health.png", 75,675,130,30, CCollisionRectangle(0,0,0,0)); 


	setUpAnimation(4,4);
	setOrgin(getWidth()/2.0f, getHeight());
	bulletcheck = SDL_GetTicks();

	timeCheck = SDL_GetTicks();
	follow = false;
	firebullet = false;
	distance = 0;
	bullet_distance = 0;
	stopAnimation = false;

}


CMainCharacter::~CMainCharacter(void)
{


	delete healthbar;
	if(firebullet)
	deleteBullet();

}



void CMainCharacter::draw()
{

	if(health == 0 || health < 0)
	{

	}
	else
	{
		
		CMovingSprite::draw();
		healthbar->setWidth(health);
		healthbar->draw();
		fire();
		if(firebullet)
		{
			bullet->draw();
		}


	}

}
void CMainCharacter::updateAnimations()
{
	//generell move animation
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
void CMainCharacter::updateControls()
{




	if (timeCheck+10 < SDL_GetTicks() && follow)
	{

		distance = getDistance(getX(), getY(), follow_Point_X, follow_Point_Y);

		if (distance == 0)
			stopAnimation = true;
		else
			stopAnimation = false;


		


		if (distance > 15)
		{
			if (getX() != follow_Point_X)
			{
				setX( getX() -  ((getX()-follow_Point_X)/distance) * 1.5f );
			}

			if (getY() != follow_Point_Y)
			{
				setY( getY() -  ((getY()-follow_Point_Y)/distance) * 1.5f );
			}
		}
		else
		{
			follow = false;
		}
		timeCheck = SDL_GetTicks();
	}
}

void CMainCharacter::update()
{
	
	updateAnimations();
	updateControls();
	collidingEffter();

}

CSprite* CMainCharacter::getHealthbar()
{
	return healthbar;
}
void CMainCharacter::fire()
{



	if(firebullet)
	{


		if (anglez > 45 && anglez <= 135)
		{
			bullet->playAnimation(0,7,2,200);
			bullet_Follow_X = bobcurrentx + 200;
			bullet_Follow_Y = bobcurrenty - 450;
			bullet_distance = getDistance(bullet->getX(), bullet->getY(), bullet_Follow_X, bullet_Follow_Y);

			//up
			if (bullet_distance > 215)
			{
				if (bullet->getY() != bullet_Follow_Y)
				{

					bullet->setY( bullet->getY() -  ((bullet->getY()-bullet_Follow_Y)/bullet_distance) * 0.09f  );
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
			bullet->playAnimation(0,7,4,200);
			bullet_Follow_X = bobcurrentx + 450;
			bullet_Follow_Y = bobcurrenty - 200;
			bullet_distance = getDistance(bullet->getX(), bullet->getY(), bullet_Follow_X, bullet_Follow_Y);

			//right
			if (bullet_distance > 215)
			{
				if (bullet->getX() != bullet_Follow_X)
				{

					bullet->setX( bullet->getX() -  ((bullet->getX()-bullet_Follow_X)/bullet_distance) *  0.09f  );

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
			bullet->playAnimation(0,7,6,200);
			bullet_Follow_X = bobcurrentx - 200;
			bullet_Follow_Y = bobcurrenty + 450;
			bullet_distance = getDistance(bullet->getX(), bullet->getY(), bullet_Follow_X, bullet_Follow_Y);

			//down
			if (bullet_distance > 215)
			{
				if (bullet->getY() != bullet_Follow_Y)
				{

					bullet->setY( bullet->getY() -  ((bullet->getY()-bullet_Follow_Y)/bullet_distance) *  0.09f  );

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
			bullet->playAnimation(0,7,0,200);
			bullet_Follow_X = bobcurrentx - 450;
			bullet_Follow_Y = bobcurrenty - 200;
			bullet_distance = getDistance(bullet->getX(), bullet->getY(), bullet_Follow_X, bullet_Follow_Y);

			//left
			if (bullet_distance > 215)
			{
				if (bullet->getX() != bullet_Follow_X)
				{

					bullet->setX( bullet->getX() -  ((bullet->getX()-bullet_Follow_X)/bullet_distance) *  0.09f  );


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


CMainCharacter* CMainCharacter::getInstance(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect, CSDL_Setup* passed_SDL_Setup)
{
	return new CMainCharacter(passed_renderer, FilePath, x, y, w, h, passed_CollisionRect,passed_SDL_Setup);
}
void CMainCharacter::mouseDown(const SDL_Event& e)
{

	if (e.button.button == SDL_BUTTON_LEFT)
	{
		follow_Point_X = e.button.x;
		follow_Point_Y = e.button.y;

		follow = true;
	}


}
void CMainCharacter::keyDown(const SDL_Event& e)
{




	if (e.key.keysym.sym)
	{
		if (SDLK_SPACE)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_SPACE:

				if(create)
				{
					bullet = new CSprite(csdl_setup->getRenderer(), "data/fireball_1.png", getX(),getY(),100,120, CCollisionRectangle(0,50,75,75)); 
					bullet->setUpAnimation(8,8);
					bullet->setOrgin(bullet->getWidth()/2.0f, bullet->getHeight());
					firebullet = true;

					bobcurrentx = getX();
					bobcurrenty = getY();
					anglez = atan2(follow_Point_Y - getY(), follow_Point_X - getX());
					anglez = (anglez * (180/3.14)) + 180;
					create = false;
				}

				break;

			default:
				break;
			}


		}

	}


}


void CMainCharacter::collidingEffter()
{
	
	for(std::vector<CSprite*>::iterator it = borders.begin(); it != borders.end(); it++)
		{
			if(this->isColliding((*it)->getCollisionRect()))
			{
				if (getX() > follow_Point_X)
 				{
 					setX(getX() + 15);
					setHealth(health - 5);
					follow_Point_X = getX();
 
 				}
 				if (getX() < follow_Point_X)
 				{
 					setX(getX() - 15);
					setHealth(health - 5);
					follow_Point_X = getX();
 				}
 
 				if (getY() > follow_Point_Y)
 				{
 					setY(getY() + 15);
					setHealth(health - 5);
					follow_Point_Y = getY();
 				}
 				if (getY() < follow_Point_Y)
 				{
 					setY(getY() - 15);
					setHealth(health - 5);
					follow_Point_Y = getY();
 				}
				
			}
		}
		for(std::vector<CSprite*>::iterator it = enemies.begin(); it != enemies.end(); it++)
		{
			if(this->isColliding((*it)->getCollisionRect()))
			{
				if (getX() > follow_Point_X)
 				{
 					(*it)->setX((*it)->getX() + 15);
					setHealth(health - 5);
				
 
 				}
 				if (getX() < follow_Point_X)
 				{
 					(*it)->setX((*it)->getX() - 15);
					setHealth(health - 5);
					
 				}
 
 				if (getY() > follow_Point_Y)
 				{
 					(*it)->setY((*it)->getY() + 15);
					setHealth(health - 5);
					
 				}
 				if (getY() < follow_Point_Y)
 				{
 					(*it)->setY((*it)->getY() - 15);
					setHealth(health - 5);
					
 				}
				
			}
		}

}
void CMainCharacter::deleteBullet()
{
	firebullet = false;
	create = true;
	delete bullet;
	
}
void CMainCharacter::addEnemies(CSprite* comp)
{
	enemies.push_back(comp);
}
void CMainCharacter::addBorders(CSprite* comp)
{
	borders.push_back(comp);
}