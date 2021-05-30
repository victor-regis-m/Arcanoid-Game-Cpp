#pragma once
#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Beveler.h"

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
	Vec2 GetPosition();
private:
	RectF rect;
	static constexpr float padding = 0.5f;
	static constexpr int bevelSize = 3;
	Beveler bev;
	bool isDestroyed=false;
};