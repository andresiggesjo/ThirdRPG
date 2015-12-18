#include "CollisionRectangle.h"
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

CCollisionRectangle::CCollisionRectangle()
{
	offsetX = 0;
	offsetY = 0;
	setRectangle(0,0,0,0);
}

CCollisionRectangle::CCollisionRectangle(int x, int y, int w, int h)
{
	offsetX = x;
	offsetY = y;
	setRectangle(0, 0, w, h);
}


CCollisionRectangle::~CCollisionRectangle(void)
{
}

void CCollisionRectangle::setRectangle(int x, int y, int w, int h)
{
	collisionRect.x = x + offsetX;
	collisionRect.y = y + offsetY;
	collisionRect.w = w;
	collisionRect.h = h;
}
