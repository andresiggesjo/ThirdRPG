#include "StdAfx.h"
#include "Sprite.h"
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

CSprite::CSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_collisionRect)
{	
	collisionRect = passed_collisionRect;
	renderer = passed_renderer;
	image = NULL;
	image = IMG_LoadTexture(renderer,FilePath.c_str());

	if (image == NULL)
	{
		std::cout << "Couldn't Load " << FilePath.c_str() << std::endl;
	}

	collisionImage = NULL;
 
    collisionImage = IMG_LoadTexture(renderer, "data/CollisionBox.png");
 
    if (collisionImage == NULL)
    {
        std::cout << "Couldn't Load " << "CollisionImage" << std::endl;
    }

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_QueryTexture(image,NULL,NULL, &img_width, &img_height);

	crop.x = 0;
	crop.y = 0;
	crop.w = img_width;
	crop.h = img_height;

	x_pos = x;
	y_pos = y;

	orgin_X = 0;
	orgin_Y = 0;

	currentFrame = 0;
	amount_Frame_X = 0;
	amount_Frame_Y = 0;
}

void CSprite::setUpAnimation(int passed_Amount_X, int passed_Amount_Y)
{
	amount_Frame_X = passed_Amount_X;
	amount_Frame_Y = passed_Amount_Y;
}

void CSprite::playAnimation(int beginFrame, int endFrame, int row, float speed)
{
	if (animationDelay+speed < SDL_GetTicks())
	{

	if (endFrame <= currentFrame)
		currentFrame = beginFrame;
	else
		currentFrame++;

	crop.x = currentFrame * (img_width/amount_Frame_X);
	crop.y = row * (img_height/amount_Frame_Y);
	crop.w = img_width/amount_Frame_X;
	crop.h = img_height/amount_Frame_Y;

	animationDelay = SDL_GetTicks();
	}
}

CSprite::~CSprite(void)
{
	SDL_DestroyTexture(image);
}

void CSprite::draw()
{

	collisionRect.setX(rect.x);
    collisionRect.setY(rect.y);
	
	SDL_RenderCopy(renderer,image, &crop, &rect);
	//SDL_RenderCopy(renderer,CollisionImage, NULL, &collisionRect.GetRectangle());
	
}


void CSprite::setX(float X)
{
	x_pos = X;

	rect.x = int(x_pos - orgin_X);
}

void CSprite::setY(float Y)
{
	y_pos = Y;

	rect.y = int(y_pos - orgin_Y);
}

void CSprite::setPosition(float X, float Y)
{
	x_pos = X;
	y_pos = Y;

	rect.x = int(x_pos - orgin_X);
	rect.y = int(y_pos - orgin_Y);
}

float CSprite::getX()
{
	return x_pos;
}

float CSprite::getY()
{
	return y_pos;
}

void CSprite::setOrgin(float X, float Y)
{
	orgin_X = X;
	orgin_Y = Y;

	setPosition(getX(), getY());

}

void CSprite::setWidth(int W)
{
	rect.w = W;
}

void CSprite::setHeight(int H)
{
	rect.h = H;
}

int CSprite::getWidth()
{
	return rect.w;
}

int CSprite::getHeight()
{
	return rect.h;
}

bool CSprite::isColliding(CCollisionRectangle theCollider)
{
    return !(collisionRect.getRectangle().x + collisionRect.getRectangle().w < theCollider.getRectangle().x || collisionRect.getRectangle().y + collisionRect.getRectangle().h < theCollider.getRectangle().y
		|| collisionRect.getRectangle().x > theCollider.getRectangle().x + theCollider.getRectangle().w || collisionRect.getRectangle().y > theCollider.getRectangle().y + theCollider.getRectangle().h);
}

void CSprite::update()
{

}
void CSprite::resetCollisionRect()
{
	
	collisionRect.setRectangle(0,0,0,0);

}