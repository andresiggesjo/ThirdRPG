#include "StdAfx.h"
#include "Main.h"
#include <algorithm>
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

CMain::CMain(int passed_ScreenWidth, int passed_ScreenHeight)
{
	ScreenWidth = passed_ScreenWidth;
	ScreenHeight = passed_ScreenHeight;
	quit = false;
	csdl_setup = new CSDL_Setup(&quit, ScreenWidth, ScreenHeight);


	grass = new CSprite(csdl_setup->GetRenderer(),"data/grass.bmp", 0, 0, ScreenWidth, ScreenHeight, CCollisionRectangle(0, 0, 0, 0));


	//borders
	//fixa colliders i envinorment
	borders.push_back(new CSprite(csdl_setup->GetRenderer(),"data/Thorn.png", 0, 0,  75, ScreenHeight, CCollisionRectangle(0, 0, 75, ScreenHeight)));
	borders.push_back(new CSprite(csdl_setup->GetRenderer(),"data/Thorn.png", 0, 0,  ScreenWidth, 75, CCollisionRectangle(0, 0, ScreenWidth, 75)));
	borders.push_back(new CSprite(csdl_setup->GetRenderer(),"data/Thorn.png", ScreenWidth-75, 0,  75, ScreenHeight, CCollisionRectangle(0, 0, 75, ScreenHeight)));
	borders.push_back(new CSprite(csdl_setup->GetRenderer(),"data/Thorn.png", 0, ScreenHeight-75,  ScreenWidth, 75, CCollisionRectangle(0, 0, ScreenWidth, 75)));

	MouseX = 0;
	MouseY = 0;

	bob = new CMainCharacter(csdl_setup,&MouseX,&MouseY,borders);

	enemy = new CEnemy(csdl_setup, bob, 500,400, borders);
	enemy1 = new CEnemy(csdl_setup, bob, 600,300, borders);
	gameObjects.push_back(bob);

	gameObjects1.push_back(enemy);
	gameObjects1.push_back(enemy1);
	//addPlayer(bob);
	//addEnemy(enemy, bob,500,400);
	//addEnemy(enemy1, bob,600,300);
}


CMain::~CMain(void)
{
	delete csdl_setup;
	delete grass;


	for(std::vector<CSprite*>::iterator it = borders.begin(); it != borders.end(); ++it) {
		delete (*it);
		(*it) = nullptr;
	}	
		
	borders.clear();

	for(std::vector<CMainCharacter*>::iterator it = gameObjects.begin(); it != gameObjects.end(); ++it) {
		delete (*it); 
		(*it) = nullptr;


	}	
		
	gameObjects.clear();

	for(std::vector<CEnemy*>::iterator it = gameObjects1.begin(); it != gameObjects1.end(); ++it) {
		delete (*it);
		(*it) = nullptr;
	}	
		
	gameObjects1.clear();


}
void CMain::addPlayer(CMainCharacter* passed_player)
{
	passed_player = new CMainCharacter(csdl_setup,&MouseX,&MouseY,borders);
	//gameObjects.push_back(passed_player);
}
void CMain::addEnemy(CEnemy* enemy,CMainCharacter* player, int startx, int starty)
{
	enemy = new CEnemy(csdl_setup,player,startx,starty, borders);
	//gameObjects.push_back(enemy);
}
void CMain::addBorders()
{
	borders.push_back(new CSprite(csdl_setup->GetRenderer(),"data/Thorn.png", 0, 0,  75, ScreenHeight, CCollisionRectangle(0, 0, 75, ScreenHeight)));
	borders.push_back(new CSprite(csdl_setup->GetRenderer(),"data/Thorn.png", 0, 0,  ScreenWidth, 75, CCollisionRectangle(0, 0, ScreenWidth, 75)));
	borders.push_back(new CSprite(csdl_setup->GetRenderer(),"data/Thorn.png", ScreenWidth-75, 0,  75, ScreenHeight, CCollisionRectangle(0, 0, 75, ScreenHeight)));
	borders.push_back(new CSprite(csdl_setup->GetRenderer(),"data/Thorn.png", 0, ScreenHeight-75,  ScreenWidth, 75, CCollisionRectangle(0, 0, ScreenHeight, 75)));
	//gameObjects.push_back(border på ngt sätt haha);
}





void CMain::GameLoop(void)
{
	if(csdl_setup->GetMainEvent()->type == SDL_QUIT)
	{
		std::cout<<"hej"<<std::endl;
	}

	while (!quit && csdl_setup->GetMainEvent()->type != SDL_QUIT)
	{
		csdl_setup->Begin();
		SDL_GetMouseState(&MouseX,&MouseY);

		grass->Draw();
		for (std::vector<CSprite*>::iterator i = borders.begin(); i != borders.end(); ++i)
		{
			(*i)->Draw();

		}

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
