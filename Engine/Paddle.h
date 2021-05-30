#pragma once
#include "Vec2.h"
#include "MainWindow.h"
#include "Graphics.h"

class Paddle
{
public:
	Paddle() = default;
	Paddle(Vec2& startingPosition);
	void Move(MainWindow& wnd, float dt);
	void Draw(Graphics& gfx);
	float GetLeftEdgePos();
	float GetRightEdgePos();
	bool isInsidePaddle(const Vec2& point);
	void AdjustPadPosition(float difference);
	int LastMovement();
	Vec2 PaddlePos();
	static constexpr float ballVelocityGain = 20;
private:
	Vec2 position;
	Vec2 lastPosition;
	static constexpr int width=70;
	static constexpr int height=15;
	static constexpr float moveSpeed = 250;
 };