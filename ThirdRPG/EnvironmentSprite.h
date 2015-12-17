#pragma once
#include "sprite.h"
#include "SDL_Setup.h"
#include "MovingSprite.h"
class CEnvironmentSprite :
	public CSprite
{
public:
	CEnvironmentSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect);
	~CEnvironmentSprite(void);

	static CEnvironmentSprite* getInstance(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect);
	bool shouldCollideWith(CSprite* sprite);
	

private:


};

