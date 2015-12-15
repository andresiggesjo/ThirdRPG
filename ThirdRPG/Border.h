#pragma once
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Sprite.h"
 
class CBorder
{
public:
    CBorder(int x, int y, CSDL_Setup* csdl_setup);
    ~CBorder(void);
 
    void DrawBorder();
	void Update();
 
    int GetX();
    int GetY();
 
    CSprite* GetBorder1() { return border1; }
	CSprite* GetBorder2() { return border2; }
	CSprite* GetBorder3() { return border3; }
	CSprite* GetBorder4() { return border4; }


 
private:
    int x, y;
    CSprite* border1;
	CSprite* border2;
	CSprite* border3;
	CSprite* border4;

 

};