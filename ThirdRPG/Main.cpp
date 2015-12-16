#include "StdAfx.h"
#include "Main.h"
#include <algorithm>

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

CMain::CMain(int passed_ScreenWidth, int passed_ScreenHeight, CSDL_Setup* passed_SDL_Setup)
{
	ScreenWidth = passed_ScreenWidth;
	ScreenHeight = passed_ScreenHeight;
	quit = false;
	
	csdl_setup = passed_SDL_Setup;



	MouseX = 0;
	MouseY = 0;

	//bob = new CMainCharacter(csdl_setup,&MouseX,&MouseY,borders);


	

}


CMain::~CMain(void)
{



}
void CMain::addBackground(CSprite* background)
{

	gameEntities.push_back(background);
}
void CMain::addPlayer(CMovingSprite* player)
{
	gameEntities.push_back(player);
}

void CMain::addEnemy(CEnemy* enemy)
{
	gameEntities.push_back(enemy);

}
void CMain::addBorders(CSprite* border1, CSprite* border2, CSprite* border3, CSprite* border4)
{
	gameEntities.push_back(border1);
	gameEntities.push_back(border2);
	gameEntities.push_back(border3);
	gameEntities.push_back(border4);
}





void CMain::GameLoop(void)
{
	if(csdl_setup->GetMainEvent()->type == SDL_QUIT)
	{

	}

	while (!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		csdl_setup->Begin();
		SDL_GetMouseState(&MouseX,&MouseY);


		for(std::vector<CSprite*>::iterator it = gameEntities.begin(); it != gameEntities.end(); it++)
		{
			(*it)->Draw();
			(*it)->update();

		}
		for (std::vector<CSprite*>::iterator i = borders.begin(); i != borders.end(); ++i)
		{
			(*i)->Draw();

		}
		/*
		for(std::vector<CMainCharacter*>::iterator it = gameObjects.begin(); it != gameObjects.end(); )
		{
			if((*it)->getHealth() == 0 || (*it)->getHealth() < 0)
			{

				delete (*it); 
				(*it) = nullptr;
				it = gameObjects.erase(it);



			}
			else{
				(*it)->draw();
				(*it)->update();
				it++;

			}

		}
		
		*/
		
		for(std::vector<CEnemy*>::iterator it = gameObjects1.begin(); it != gameObjects1.end(); )
		{
			if((*it)->getHealth() == 0)
			{

				delete (*it);
				(*it) = nullptr;
				std::cout<<"raderad"<<std::endl;
				it = gameObjects1.erase(it);


			}
			else{
				(*it)->Draw();
				(*it)->Update();
				it++;

			}

		}

		

		csdl_setup->End();
	}
	
}
