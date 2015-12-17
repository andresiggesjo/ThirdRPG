#include "stdafx.h"
#include "Main.h"
#include "MainCharacter.h"
#include "Enemy.h"
#include "SDL_Setup.h"
#include "EnvironmentSprite.h"
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
	CMain* cmain = new CMain(ScreenWidth,ScreenHeight,csdl_setup,&MouseX, &MouseY);

	//game enteties   spelare och enemies
	CMainCharacter* bobnumerodos = CMainCharacter::getInstance(csdl_setup->GetRenderer(),"data/mainchar.png",300,250,100,120, CCollisionRectangle(30,20,50,90), csdl_setup, &MouseX, &MouseY);
	


	//Environment skit
	CEnvironmentSprite* grass =  CEnvironmentSprite::getInstance(csdl_setup->GetRenderer(),"data/grass.bmp", 0, 0, 1080, 720, CCollisionRectangle(0, 0, 0, 0));
	CEnvironmentSprite* border1 = CEnvironmentSprite::getInstance(csdl_setup->GetRenderer(),"data/Thorn.png", 0, 0,  75, ScreenHeight, CCollisionRectangle(0, 0, 75, ScreenHeight));
	CEnvironmentSprite* border2 = CEnvironmentSprite::getInstance(csdl_setup->GetRenderer(),"data/Thorn.png", 0, 0,  ScreenWidth, 75, CCollisionRectangle(0, 0, ScreenWidth, 75));
	CEnvironmentSprite* border3 = CEnvironmentSprite::getInstance(csdl_setup->GetRenderer(),"data/Thorn.png", ScreenWidth-75, 0,  75, ScreenHeight, CCollisionRectangle(0, 0, 75, ScreenHeight));
	CEnvironmentSprite* border4 = CEnvironmentSprite::getInstance(csdl_setup->GetRenderer(),"data/Thorn.png", 0, ScreenHeight-75,  ScreenWidth, 75, CCollisionRectangle(0, 0, ScreenWidth, 75));

	//lägg till allt i spelmotorn
	cmain->addBackground(grass);
	cmain->addBorders(border1, border2, border3, border4);
	cmain->addPlayer(bobnumerodos);
	
	CEnemy* enemynumerouno = CEnemy::getInstance(csdl_setup->GetRenderer(),"data/enemy.png",500,400,100,100, CCollisionRectangle(25,0,50,100), csdl_setup, &MouseX, &MouseY, bobnumerodos);
	cmain->addPlayer(enemynumerouno);
	//kör spelmotorns händelseloop
	cmain->GameLoop();


	// delete ALLLLT amana
	delete cmain;
	delete bobnumerodos;
	delete grass;
	delete border1;
	delete border2;
	delete border3;
	delete border4;
	delete enemynumerouno;
	delete csdl_setup;

	_CrtDumpMemoryLeaks();

	
	return 0;
}
