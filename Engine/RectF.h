#pragma once
#include "Vec2.h"
class RectF
{
public:
	RectF() = default;
	RectF(const float leftIn, const float rightIn, const float topIn, const float bottomIn);
	RectF(const Vec2& topLeft, const Vec2& bottomRight);
	RectF(const Vec2& topLeft, const float width, const float height);
public:
	float left;
	float right;
	float top;
	float bottom;
};