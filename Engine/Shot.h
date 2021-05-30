#pragma once
#include "Vec2.h"
#include "Graphics.h"
class Shot
{
public:
	Shot(Vec2& pos, bool state);
	void Draw(Graphics& gfx, float topLimit);
	Vec2 position;
	void operator=(Shot& other);
	static constexpr float speed = 400;
	void Move(float dt, float topLimit);
	bool isActive;
};