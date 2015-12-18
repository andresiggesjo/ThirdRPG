#pragma once
#include "stdafx.h"
#include "CollisionRectangle.h"

class CSprite
{
public:
	CSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect);
	~CSprite(void);


	virtual void update();
	virtual void draw();
	virtual int getHealth(){return health; }
	virtual void mouseDown(const SDL_Event&) {}
	virtual void mouseUp(const SDL_Event&) {}
	virtual void keyDown(const SDL_Event&) {}
	virtual void keyUp(const SDL_Event&) {}

	CCollisionRectangle getCollisionRect() { return collisionRect; }

	void setX(float X);
	void setY(float Y);
	void setPosition(float X, float Y);
	void setOrgin(float X, float Y);
	void playAnimation(int beginFrame, int endFrame, int row, float speed);
	void setUpAnimation(int passed_Amount_X, int passed_Amount_Y);
	void resetCollisionRect();
	void setWidth(int W);
	void setHeight(int H);

	float getX();
	float getY();
	
	int getWidth();
	int getHeight();

	bool isColliding(CCollisionRectangle theCollider);

private:

	float orgin_X;
	float orgin_Y;
	float x_pos;
	float y_pos;

	SDL_Renderer* renderer;
	SDL_Texture* image;
	SDL_Texture* collisionImage;
	SDL_Rect rect;
	SDL_Rect crop;

	int img_width;
	int img_height;
	int currentFrame;
	int animationDelay;
	int health;
	int amount_Frame_X;
	int amount_Frame_Y;

	CCollisionRectangle collisionRect;

	//för värdesemantik
	CSprite(const CSprite&);
	void operator=(const CSprite&);
};

