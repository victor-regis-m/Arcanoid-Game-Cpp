#pragma once

#include "RectF.h"
#include "Beveler.h"
#include "Graphics.h"

class Wall
{
public:
	Wall(const RectF& innerBounds_in, float thickness_in, Color baseColor);
	const RectF& GetInnerBounds() const;
	void Draw(Graphics& gfx) const;
private:
	RectF innerBounds;
	float thickness;
	Beveler bev;
};