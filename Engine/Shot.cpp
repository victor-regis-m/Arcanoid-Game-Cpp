#include "Shot.h"

Shot::Shot(Vec2& pos, bool state)
	:
	position(pos),
	isActive(state)
{
}

void Shot::Draw(Graphics& gfx, float topLimit)
{
	if(position.y>topLimit)
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
				gfx.PutPixel(position.x + i, position.y + j, Color(255, 255, 255));
}

void Shot::operator=(Shot& other)
{
	position = other.position;
	isActive = other.isActive;
}

void Shot::Move(float dt, float topLimit)
{
	if (position.y > topLimit)
		position += Vec2(0, -speed) * dt;
	else
		isActive = false;
}
