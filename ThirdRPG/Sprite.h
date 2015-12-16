#pragma once

#include "stdafx.h"
#include "CollisionRectangle.h"
class CSprite
{
public:
	CSprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h, CCollisionRectangle passed_CollisionRect);
	~CSprite(void);
	CSprite();

	virtual void Draw();

	CCollisionRectangle GetCollisionRect() { return CollisionRect; }
	void SetX(float X);
	void SetY(float Y);
	void SetPosition(float X, float Y);

	float GetX();
	float GetY();
	
	void SetWidth(int W);
	void SetHeight(int H);
	int GetWidth();
	int GetHeight();

	void update();
	void SetOrgin(float X, float Y);
	void PlayAnimation(int BeginFrame, int EndFrame, int Row, float Speed);
	void SetUpAnimation(int passed_Amount_X, int passed_Amount_Y);

	bool isColliding(CCollisionRectangle theCollider);
private:
	float Orgin_X;
	float Orgin_Y;

	float X_pos;
	float Y_pos;

	SDL_Texture* image;
	SDL_Texture* CollisionImage;
	SDL_Rect rect;

	SDL_Rect crop;

	int img_width;
	int img_height;
	int CurrentFrame;
	int animationDelay;

	int Amount_Frame_X;
	int Amount_Frame_Y;

	SDL_Renderer* renderer;

	CCollisionRectangle CollisionRect;
};