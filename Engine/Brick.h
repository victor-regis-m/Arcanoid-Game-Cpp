#pragma once
#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
class Brick
{
public:
	Brick(const RectF& rectIn, Color cIn);
	Brick() = default;
	void Draw(Graphics& gfx);
	RectF GetRect();
	bool isInsideBrick(const Vec2& point);
	bool isSidewaysColision(const Vec2& center);
	bool isTopBottomColision(const Vec2& center);
	bool isOnBrickLeft(const Vec2& center);
	bool isOnBrickBottom(const Vec2& center);
	void DestroyBrick();
private:
	RectF rect;
	Color c;
	bool isDestroyed=false;
};