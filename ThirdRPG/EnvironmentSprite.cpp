#include "StdAfx.h"
#include "EnvironmentSprite.h"
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG


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