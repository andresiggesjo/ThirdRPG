#include "StdAfx.h"
#include "Border.h"
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

CBorder::CBorder(int x_passed, int y_passed, CSDL_Setup* csdl_setup)
{

 
    x = x_passed;
    y = y_passed;
 
    border1 = new CSprite(csdl_setup->GetRenderer(),"Thorn.png", x, y, 355, 200, CCollisionRectangle(x,y,355,200));
	border2 = new CSprite(csdl_setup->GetRenderer(),"Thorn.png", x, y, 355, 200, CCollisionRectangle(x,y,355,200));
	border3 = new CSprite(csdl_setup->GetRenderer(),"Thorn.png", x, y, 355, 200, CCollisionRectangle(x,y,355,200));
	border4 = new CSprite(csdl_setup->GetRenderer(),"Thorn.png", x, y, 355, 200, CCollisionRectangle(x,y,355,200));
   
}


CBorder::~CBorder(void)
{
	delete border1;
	delete border2;
	delete border3;
	delete border4;
}


int CBorder::GetX()
{
    return x;
}
 
int CBorder::GetY()
{
    return y;
}
 
void CBorder::DrawBorder()
{
	border1->Draw();
	border2->Draw();
	border3->Draw();
	border4->Draw();
}
void CBorder::Update()
{

}