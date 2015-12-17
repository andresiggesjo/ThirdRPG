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




}


CMain::~CMain(void)
{



}


void CMain::add(CSprite* comp)
{
	gameEntities.push_back(comp);
}




void CMain::GameLoop(void)
{
	csdl_setup->Begin();
	SDL_RenderClear(csdl_setup->GetRenderer());

	SDL_RenderPresent(csdl_setup->GetRenderer());
	bool goOn = true;
	while (goOn) {
		SDL_Event eve;
		while (SDL_PollEvent(&eve)) {
			switch (eve.type) {
			case SDL_QUIT: goOn = false; break;
			case SDL_MOUSEBUTTONDOWN:
				for(std::vector<CSprite*>::iterator it = gameEntities.begin(); it != gameEntities.end(); it++)
					(*it)->mouseDown(eve);
				break;
			case SDL_MOUSEMOTION:
				for(std::vector<CSprite*>::iterator it = gameEntities.begin(); it != gameEntities.end(); it++)
					(*it)->mouseDown(eve);
				break;
			case SDL_KEYDOWN:
				for(std::vector<CSprite*>::iterator it = gameEntities.begin(); it != gameEntities.end(); it++)
					(*it)->keyDown(eve);
				break;
			} // switch
		} // inre while

		SDL_RenderClear(csdl_setup->GetRenderer());


		for(std::vector<CSprite*>::iterator it = gameEntities.begin(); it != gameEntities.end();)
		{
			if((*it)->getHealth() == 0)
			{
				(*it)->resetCollisionRect();

				/*
				delete (*it); 
				(*it) = nullptr;
				it = gameEntities.erase(it);
				*/
				
			}
			(*it)->Draw();
			(*it)->update();
			it++;
		}
		SDL_RenderPresent(csdl_setup->GetRenderer());

	} // yttre while

	csdl_setup->End();


}
