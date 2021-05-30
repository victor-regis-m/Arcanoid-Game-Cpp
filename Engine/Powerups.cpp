#include "Powerups.h"

Powerups::Powerups(bool state, Vec2& spawnPos)
	:
	isActive(state),
	position(spawnPos),
	rd(),
	gen(rd()),
	distrib(0, 2),
	type(distrib(gen)),
	bev(c[type]),
	rect(position + Vec2(width / 2, height / 2), position - Vec2(width / 2, height / 2))
{
}


bool Powerups::GeneratePowerUp()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distrib(1, 100);
	if (distrib(gen) <= 13)
		return true;
	else
		return false;
}

void Powerups::Move(float dt)
{
	position += Vec2(0.0f, speed) * dt;
	rect = RectF(position + Vec2(width / 2, height / 2), position - Vec2(width / 2, height / 2));
}

void Powerups::Draw(Graphics& gfx)
{
	if(isActive)
		bev.DrawBeveledBrick(rect.GetExpanded(-0.1), bevelSize, gfx);
}

int Powerups::GetType()
{
	return type;
}

void Powerups::Activate()
{
	isActive = true;
}

void Powerups::Deactivate()
{
	isActive = false;
}

Vec2 Powerups::GetTopLeft()
{
	return position - Vec2(width / 2, height / 2);
}

Vec2 Powerups::GetBottomRight()
{
	return position + Vec2(width / 2, height / 2);
}

Vec2 Powerups::GetPosition()
{
	return position;
}

bool Powerups::IsActive()
{
	return isActive;
}


