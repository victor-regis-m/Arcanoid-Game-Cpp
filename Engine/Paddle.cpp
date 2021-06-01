#include "Paddle.h"

Paddle::Paddle(Vec2& startingPosition)
	:
	position(startingPosition),
	lastPosition(startingPosition)
{
}

void Paddle::Move(MainWindow& wnd, float dt)
{
	lastPosition = position;
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
		position -= Vec2(moveSpeed, 0) * dt;
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		position += Vec2(moveSpeed, 0) * dt;	
}

void Paddle::Draw(Graphics& gfx)
{
	gfx.DrawRect(RectF(position + Vec2(width / 2, height / 2), position - Vec2(width / 2, height / 2)), Color(255,240,200));
	gfx.DrawRect(RectF(position + Vec2(width / 2.5f, height / 2), position - Vec2(width / 2.5f, height / 2)), Color(220, 180, 100));
	if (isWeaponActive)
	{
		gfx.DrawRect(RectF(position + Vec2(width / 2.4f, -height / 2), position + Vec2(width / 2.2f, -height / 1.3f)), Color(220, 190, 200));
		gfx.DrawRect(RectF(position - Vec2(width / 2.2f, height / 1.3f), position - Vec2(width / 2.4f, height / 2)), Color(220, 190, 200));
	}
		
}

float Paddle::GetLeftEdgePos()
{
	return position.x - (float)width/2;
}

float Paddle::GetRightEdgePos()
{
	return position.x + (float)width / 2;
}

bool Paddle::isInsidePaddle(const Vec2& point)
{
	return (point.x < position.x + width / 2 && point.x > position.x - width / 2
		&& point.y < position.y + height / 2 && point.y > position.y - height / 2);
}

void Paddle::AdjustPadPosition(float difference)
{
	position.x += difference;
}

bool Paddle::PickUpPowerUp(Powerups& pwr)
{ 
	int left = position.x - width / 2;
	int right = position.x + width / 2;
	int bottom = position.y + height / 2;
	int top = position.y - height / 2;
	Vec2 pwrTopLeft = pwr.GetTopLeft();
	Vec2 pwrBottomRight = pwr.GetBottomRight();
	if (right > pwrTopLeft.x && left < pwrBottomRight.x && bottom > pwrTopLeft.y && top < pwrBottomRight.y)
	{
		pwr.Deactivate();
		return true;
	}
	return false;
}

int Paddle::LastMovement()
{
	if (lastPosition.x > position.x)
		return -1;
	if (lastPosition.x < position.x)
		return 1;
	if (lastPosition.x == position.x)
		return 0;
}

Vec2 Paddle::PaddlePos()
{
	return position;
}

Vec2 Paddle::GetLeftCannonPos()
{
	return position - Vec2(width/2.3f, height/1.5f);
}

Vec2 Paddle::GetRightCannonPos()
{
	return  position + Vec2(width / 2.3f, -height / 1.3f);
}

void Paddle::SetPos(Vec2& newPos)
{
	position = newPos;
}
