#include "stdafx.h"
#include "Main.h"
#include "MainCharacter.h"
#include "Enemy.h"
#include "SDL_Setup.h"
#include "EnvironmentSprite.h"
#include <vector>
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

	std::vector<CSprite*> colliders;

	const int ScreenHeight = 720;
	const int ScreenWidth = 1080;

	CSDL_Setup* csdl_setup = new CSDL_Setup(false, ScreenWidth, ScreenHeight);
	CMain* cmain = new CMain(ScreenWidth,ScreenHeight,csdl_setup,&MouseX, &MouseY);

	//game enteties   spelare och enemies
	CMainCharacter* bobnumerodos = CMainCharacter::getInstance(csdl_setup->GetRenderer(),"data/mainchar.png",300,250,100,120, CCollisionRectangle(30,20,50,90), csdl_setup, &MouseX, &MouseY);
	CEnemy* enemynumerouno = CEnemy::getInstance(csdl_setup->GetRenderer(),"data/enemy.png",500,400,100,100, CCollisionRectangle(25,0,50,100), csdl_setup, &MouseX, &MouseY, bobnumerodos);
	

	//Environment skit
	CEnvironmentSprite* grass =  CEnvironmentSprite::getInstance(csdl_setup->GetRenderer(),"data/grass.bmp", 0, 0, 1080, 720, CCollisionRectangle(0, 0, 0, 0));
	CEnvironmentSprite* border1 = CEnvironmentSprite::getInstance(csdl_setup->GetRenderer(),"data/Thorn.png", 0, 0,  75, ScreenHeight, CCollisionRectangle(0, 0, 75, ScreenHeight));
	CEnvironmentSprite* border2 = CEnvironmentSprite::getInstance(csdl_setup->GetRenderer(),"data/Thorn.png", 0, 0,  ScreenWidth, 75, CCollisionRectangle(0, 0, ScreenWidth, 75));
	CEnvironmentSprite* border3 = CEnvironmentSprite::getInstance(csdl_setup->GetRenderer(),"data/Thorn.png", ScreenWidth-75, 0,  75, ScreenHeight, CCollisionRectangle(0, 0, 75, ScreenHeight));
	CEnvironmentSprite* border4 = CEnvironmentSprite::getInstance(csdl_setup->GetRenderer(),"data/Thorn.png", 0, ScreenHeight-75,  ScreenWidth, 75, CCollisionRectangle(0, 0, ScreenWidth, 75));
	colliders.push_back(border1);
	colliders.push_back(border2);
	colliders.push_back(border3);
	colliders.push_back(border4);
	bobnumerodos->setColliders(colliders);
	
	//lägg till allt i spelmotorn
	cmain->add(grass);
	cmain->add(border1);
	cmain->add(border2);
	cmain->add(border3);
	cmain->add(border4);
	cmain->add(bobnumerodos);
	cmain->add(enemynumerouno);

	//kör spelmotorns händelseloop
	cmain->GameLoop();


	// delete ALLLLT amana
	delete cmain;
	delete bobnumerodos;
	delete grass;
	delete enemynumerouno;
	delete csdl_setup;

	_CrtDumpMemoryLeaks();

	
	return 0;
}
