#include "RectF.h"

RectF::RectF(const float leftIn, const float rightIn, const float topIn, const float bottomIn)
	:
	left(leftIn),
	right(rightIn),
	top(topIn),
	bottom(bottomIn)
{
}

RectF::RectF(const Vec2& topLeft, const Vec2& bottomRight)
	:
	RectF(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

RectF::RectF(const Vec2& topLeft, const float width, const float height)
	:
	RectF(topLeft, topLeft + Vec2(width, height))
{
}

