#include "Brick.h"
Brick::Brick(const RectF& rectIn, Color cIn)
	:
	rect(rectIn),
	bev(cIn)
{

}
void Brick::Draw(Graphics& gfx)
{
	if(!isDestroyed)
		bev.DrawBeveledBrick(rect.GetExpanded(-padding), bevelSize, gfx);
}

RectF Brick::GetRect()
{
	return rect;
}

bool Brick::isInsideBrick(const Vec2& point)
{
	return (point.x < rect.right && point.x > rect.left 
		&& point.y < rect.bottom && point.y > rect.top) && !isDestroyed;
}

bool Brick::isSidewaysColision(const Vec2& center)
{
	return center.y > rect.top + 2 && center.y < rect.bottom - 2;
}

bool Brick::isTopBottomColision(const Vec2& center)
{
	return center.x > rect.left + 2 && center.x < rect.right - 2;
}

bool Brick::isOnBrickLeft(const Vec2& center)
{
	return center.x < rect.left;
}

bool Brick::isOnBrickBottom(const Vec2& center)
{
	return center.y > rect.bottom;
}

void Brick::DestroyBrick()
{
	isDestroyed = true;
}

Vec2 Brick::GetPosition()
{
	return Vec2((rect.right + rect.left) / 2, (rect.top + rect.bottom) / 2);
}
