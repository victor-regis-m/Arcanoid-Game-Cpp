#pragma once
#include "Vec2.h"
#include "SpriteCodex.h"
#include "Brick.h"
#include <math.h>   

class Ball
{
public:
	Ball(const Vec2& pos, const Vec2& vel);
	void Draw(Graphics& gfx);
	void Move(float dt);
	void DetectBrickCollision(Brick& brick, float dt);
	void ResetPosition( float dt);
	void BounceOffSurface( Vec2& normal);
	void DetectWallCollision(RectF& wall, float dt);
	void CheckForNormalBrickCollision(Vec2& normal, Brick& brick) const;
	int LeadingPointSelector();
private:
	const float radius = 7.0f;
	Vec2 position;
	Vec2 velocity;
	static constexpr int colliderDefinition = 20;
	Vec2 Collider[colliderDefinition];
};