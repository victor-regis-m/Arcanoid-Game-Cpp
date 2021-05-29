#pragma once

#include "RectF.h"
#include "Beveler.h"
#include "Graphics.h"

class Wall
{
public:
	Wall(const RectF& innerBoundsIn, float thicknessIn, Color baseColor);
	const RectF& GetInnerBounds() const;
	void Draw(Graphics& gfx) const;
private:
	RectF innerBounds;
	float thickness;
	Beveler bev;
};