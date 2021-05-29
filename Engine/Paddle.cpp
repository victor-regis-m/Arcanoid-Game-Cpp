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
