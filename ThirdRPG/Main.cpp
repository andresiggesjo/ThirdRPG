#include "StdAfx.h"
#include "Main.h"
#include <algorithm>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

CMain::CMain(int passed_ScreenWidth, int passed_ScreenHeight, CSDL_Setup* passed_SDL_Setup, int* passed_Mouse_X, int* passed_Mouse_Y)
{
	ScreenWidth = passed_ScreenWidth;
	ScreenHeight = passed_ScreenHeight;
	quit = false;	
	csdl_setup = passed_SDL_Setup;
	MouseX = passed_Mouse_X;
	MouseY = passed_Mouse_Y;



}


CMain::~CMain(void)
{



}
void CMain::addMouseMovement(CMovingSprite* objtocontrol)
{
	objtocontrol->setMouseFollow(true);
}
void CMain::addBackground(CEnvironmentSprite* background)
{

	gameEntities.push_back(background);
}
void CMain::addPlayer(CMovingSprite* player)
{
	gameEntities.push_back(player);
}

void CMain::addEnemy(CEnemy* enemy)
{
	//gameEntities.push_back(enemy);

}
void CMain::addBorders(CEnvironmentSprite* border1, CEnvironmentSprite* border2, CEnvironmentSprite* border3, CEnvironmentSprite* border4)
{
	gameEntities.push_back(border1);
	gameEntities.push_back(border2);
	gameEntities.push_back(border3);
	gameEntities.push_back(border4);
}

std::vector<CSprite*> CMain::getObjects()
{
	return gameEntities;

}





void CMain::GameLoop(void)
{

	if(csdl_setup->GetMainEvent()->type == SDL_QUIT)
	{

	}

	while (!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		csdl_setup->Begin();
		SDL_GetMouseState(MouseX,MouseY);


		for(std::vector<CSprite*>::iterator it = gameEntities.begin(); it != gameEntities.end(); it++)
		{
			for(std::vector<CSprite*>::iterator itz = gameEntities.begin(); itz != gameEntities.end(); itz++)
			{


				if((*it) != (*itz))
				{
					if((*it)->isColliding((*itz)->GetCollisionRect()))
						std::cout<<"123kgb"<<std::endl;
				}

			}

			(*it)->Draw();
			(*it)->update();

		}






		csdl_setup->End();
	}

}
