#include "stdafx.h"
#include "Main.h"
#include "MainCharacter.h"
#include "Enemy.h"
#include "SDL_Setup.h"
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

int main(int argc, char *argv[])
{

	
	int MouseX = 0;
	int MouseY = 0;
	const int ScreenHeight = 720;
	const int ScreenWidth = 1080;
	CSDL_Setup* csdl_setup = new CSDL_Setup(false, ScreenWidth, ScreenHeight);
	CMain* cmain = new CMain(ScreenWidth,ScreenHeight,csdl_setup);

	//game enteties   spelare och enemies
	CMovingSprite* bobnumerodos = new CMovingSprite(csdl_setup->GetRenderer(),"data/mainchar.png", 300,250, 100,120, CCollisionRectangle(30,20,50,90), csdl_setup, &MouseX, &MouseY);
	CEnemy* enemy = new CEnemy(csdl_setup, bobnumerodos, 500,400, borders);
	CEnemy* enemy1 = new CEnemy(csdl_setup, bobnumerodos, 600,300, borders);


	
	CSprite* grass = new CSprite(csdl_setup->GetRenderer(),"data/grass.bmp", 0, 0, 1080, 720, CCollisionRectangle(0, 0, 0, 0));
	CSprite* border1 = new CSprite(csdl_setup->GetRenderer(),"data/Thorn.png", 0, 0,  75, ScreenHeight, CCollisionRectangle(0, 0, 75, ScreenHeight));
	CSprite* border2 = new CSprite(csdl_setup->GetRenderer(),"data/Thorn.png", 0, 0,  ScreenWidth, 75, CCollisionRectangle(0, 0, ScreenWidth, 75));
	CSprite* border3 = new CSprite(csdl_setup->GetRenderer(),"data/Thorn.png", ScreenWidth-75, 0,  75, ScreenHeight, CCollisionRectangle(0, 0, 75, ScreenHeight));
	CSprite* border4 = new CSprite(csdl_setup->GetRenderer(),"data/Thorn.png", 0, ScreenHeight-75,  ScreenWidth, 75, CCollisionRectangle(0, 0, ScreenWidth, 75));

	cmain->addBackground(grass);
	cmain->addBorders(border1, border2, border3, border4);
	cmain->addPlayer(bobnumerodos);
	cmain->addEnemy(enemy);
	cmain->addEnemy(enemy1);

	//cmain->addEnemy(enemy,player,500,400);
	//cmain->addEnemy(enemy1,player,600,300);
	

	cmain->GameLoop();



	delete cmain;
	delete bobnumerodos;
	delete grass;
	delete border1;
	delete border2;
	delete border3;
	delete border4;

	_CrtDumpMemoryLeaks();
	std::cout<<"memoryleak"<<std::endl;
	
	return 0;
}
