#include "Ball.h"

Ball::Ball(const Vec2& pos, const Vec2& vel)
	:
	position(pos),
	velocity(vel)
{
	const float pi = 3.14159265358979f;
	for (int i = 0; i < colliderDefinition; i++)
		Collider[i] = position + Vec2(radius * cos(2* i * pi / (float)colliderDefinition), radius * sin(2* i * pi / (float)colliderDefinition));
}

void Ball::Draw(Graphics& gfx)
{
	SpriteCodex::DrawBall(position, gfx);
}

void Ball::Move(float dt)
{
	position += velocity * dt;
	for (int i = 0; i < colliderDefinition; i++)
		Collider[i] += velocity * dt;
}

void Ball::DetectBrickCollision(Brick& brick, float dt)
{
	int startingPoint = LeadingPointSelector();
	for (int i = 0; i < colliderDefinition/2 ; i++)
	{
		int lowerBoundInt = (colliderDefinition + startingPoint - i) % colliderDefinition;
		int upperBoundInt = (colliderDefinition + startingPoint + i) % colliderDefinition;
		if (lowerBoundInt != upperBoundInt)
		{
			if (brick.isInsideBrick(Collider[lowerBoundInt]))
			{
				Vec2 normal = (position - Collider[lowerBoundInt]).GetNormalized();
				ResetPosition(dt);
				CheckForNormalBrickCollision(normal, brick);
				BounceOffSurface(normal);
				brick.DestroyBrick();
				return;
			}
			else if (brick.isInsideBrick(Collider[upperBoundInt]))
			{
				Vec2 normal = (position - Collider[upperBoundInt]).GetNormalized();
				ResetPosition(dt);
				CheckForNormalBrickCollision(normal, brick);
				BounceOffSurface(normal);
				brick.DestroyBrick();
				return;
			}
		}
		else
		{
			if (brick.isInsideBrick(Collider[lowerBoundInt]))
			{
				Vec2 normal = (position - Collider[lowerBoundInt]).GetNormalized();
				ResetPosition(dt);
				CheckForNormalBrickCollision(normal, brick);
				BounceOffSurface(normal);
				brick.DestroyBrick();
				return;
			}
		}
	}

}

void Ball::BounceOffSurface( Vec2& normal)
{
	velocity = velocity - normal*2*normal.DotProduct(velocity);
}

void Ball::DetectWallCollision(RectF& wall, float dt)
{
	if (Collider[colliderDefinition*3/4].y <= wall.top)
	{
		ResetPosition(dt);
		BounceOffSurface(Vec2(0, 1));
	}
	if (Collider[colliderDefinition/4].y >= wall.bottom)
	{
		ResetPosition(dt);
		BounceOffSurface(Vec2(0, -1));
	}
	if (Collider[colliderDefinition/2].x <= wall.left)
	{
		ResetPosition(dt);
		BounceOffSurface(Vec2(1, 0));
	}
	if (Collider[0].x >= wall.right)
	{
		ResetPosition(dt);
		BounceOffSurface(Vec2(-1, 0));
	}
}

void Ball::CheckForNormalBrickCollision(Vec2& normal, Brick& brick) const
{
	if (brick.isSidewaysColision(position))
		if (brick.isOnBrickLeft(position))
			normal = Vec2(-1, 0);
		else
			normal = Vec2(1, 0);
	if (brick.isTopBottomColision(position))
		if (brick.isOnBrickBottom(position))
			normal = Vec2(0, 1);
		else
			normal = Vec2(0, -1);
}

int Ball::LeadingPointSelector()
{
	float pi = 3.14159265359f;
	float velocityAngle;
	if (velocity.x > 0)
	{
		if(velocity.y>0)
			velocityAngle = atan(velocity.y / velocity.x);
		else
			velocityAngle = atan(velocity.y / velocity.x) + (float)2.0f * pi;
	}
	else if (velocity.x < 0)
	{
		if (velocity.y > 0)
			velocityAngle = atan(velocity.y / velocity.x) + pi;
		else
			velocityAngle = atan(velocity.y / velocity.x) + pi;
	}
	else
	{
		if (velocity.y > 0)
			velocityAngle = 0;
		else
			velocityAngle = pi;
	}


	if (velocity.y == 0)
	{
		if (velocity.x > 0)
			velocityAngle = pi/2;
		else
			velocityAngle = 3 * pi / 2;
	}

	for (int i = 0; i < colliderDefinition; i++)
	{
		int lowerBoundInt = 2 * i - 1;
		int upperBoundInt = 2 * i + 1;
		if (i == 0)
		{
			if ((float)upperBoundInt * (pi / (float)colliderDefinition) > velocityAngle ||
				(float)(2*colliderDefinition - 1) * (pi / colliderDefinition) <= velocityAngle)
				return 0;
		}
		else if ((float)lowerBoundInt * (pi / colliderDefinition) <= velocityAngle
			&& (float)upperBoundInt * (pi /(float) colliderDefinition) > velocityAngle)
			return i;
	}
}

void Ball::ResetPosition(float dt)
{
	position -= velocity * dt;
	for (int i = 0; i < colliderDefinition; i++)
		Collider[i] -= velocity * dt;
}