#pragma once
#include "Colors.h"
#include "Vec2.h"
#include "Graphics.h"
#include "Beveler.h"
#include <random>

class Powerups
{
public:
	Powerups(bool state, Vec2& spawnPos);
	Powerups(const Powerups&) = default;
	Powerups& operator=(const Powerups& other)
	{
		type = other.type;
		position = other.position;
		bev = other.bev;
		rect = other.rect;
		isActive = other.isActive;
		return *this;
	}
	static bool GeneratePowerUp();
	void Move(float dt);
	void Draw(Graphics& gfx);
	int GetType();
	void Activate();
	void Deactivate();
	Vec2 GetTopLeft();
	Vec2 GetBottomRight();
	Vec2 GetPosition();
	bool IsActive();
private:
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<int> distrib;
	int type;
	static constexpr Color c[3] = { Color(200, 100, 100), Color(100, 200, 100), Color(100, 100, 200) };
	Vec2 position;
	Beveler bev;
	RectF rect;
	bool isActive = true;
	static constexpr int bevelSize = 4;
	static constexpr float speed = 80;
	static constexpr int width = 10;
	static constexpr int height = 6;
};