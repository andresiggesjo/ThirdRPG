#include "StdAfx.h"
#include "SDL_Setup.h"
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

CSDL_Setup::CSDL_Setup(bool* quit, int screenWidth, int screenHeight)
{
	SDL_Init(SDL_INIT_VIDEO);
	
	window = NULL;
	window = SDL_CreateWindow("Delils Darkness!", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window couldn't be created" << std::endl;
		*quit = true;
	}

	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	mainEvent = new SDL_Event();
}


CSDL_Setup::~CSDL_Setup(void)
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;
}

SDL_Renderer* CSDL_Setup::getRenderer()
{
	return renderer;
}

SDL_Event* CSDL_Setup::getMainEvent()
{
	return mainEvent;
}

void CSDL_Setup::begin()
{
	SDL_PollEvent(mainEvent);
	SDL_RenderClear(renderer);
}

void CSDL_Setup::end()
{
	SDL_RenderPresent(renderer);
}
