
#pragma once
class CSDL_Setup
{
public:
	CSDL_Setup(bool* quit, int screenWidth, int screenHeight);
	~CSDL_Setup(void);

	SDL_Renderer* getRenderer();
	SDL_Event* getMainEvent();

	void begin();
	void end();
private:
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* mainEvent;

};

