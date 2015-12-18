#pragma once

#include "stdafx.h"

class CCollisionRectangle
{
public:
	CCollisionRectangle();
	CCollisionRectangle(int x, int y, int w, int h);
	~CCollisionRectangle(void);

	void setRectangle(int x, int y, int w, int h);
	SDL_Rect getRectangle() { return collisionRect; }

	void setX(int x) { collisionRect.x = x + offsetX; }  
	void setY(int y) { collisionRect.y = y + offsetY; }  


private:
	int offsetX;
	int offsetY;
	SDL_Rect collisionRect;
};

