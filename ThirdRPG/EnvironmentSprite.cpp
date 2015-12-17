#include "StdAfx.h"
#include "EnvironmentSprite.h"



CEnvironmentSprite::CEnvironmentSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect)
	: CSprite(passed_renderer, FilePath, x, y , w, h, passed_CollisionRect)
{


}


CEnvironmentSprite::~CEnvironmentSprite(void)
{
}




CEnvironmentSprite* CEnvironmentSprite::getInstance(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect) {
	return new CEnvironmentSprite(passed_renderer, FilePath, x, y, w, h, passed_CollisionRect);
}