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
	//Ny spelmotor
	//grass = new CSprite(csdl_setup->GetRenderer(),"data/grass.bmp", 0, 0, ScreenWidth, ScreenHeight, CCollisionRectangle(0, 0, 0, 0));
	//problem att man måste definiera player å enemy i en headerklass eller här i spelet, men måste vi definiera här i spelet behöver vi ta in väldigt mkt variabler
	CMain* cmain = new CMain(1080,720);
	//CMainCharacter* player;
	//CEnemy* enemy;
	//CEnemy* enemy1;
	
	//cmain->addPlayer(player);
	//cmain->addEnemy(enemy,player,500,400);
	//cmain->addEnemy(enemy1,player,600,300);
	
	//cmain->addEnvironment(grass);
	cmain->GameLoop();



	delete cmain;


	_CrtDumpMemoryLeaks();
	std::cout<<"memoryleak"<<std::endl;
	
	return 0;
}
