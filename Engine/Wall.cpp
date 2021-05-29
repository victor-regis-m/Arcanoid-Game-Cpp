#include "Wall.h"
#include <assert.h>

Wall::Wall(const RectF& innerBounds_in, float thickness_in, Color baseColor)
	:
	innerBounds(innerBounds_in),
	thickness(thickness_in),
	bev(baseColor)
{
}

const RectF& Wall::GetInnerBounds() const
{
	return innerBounds;
}

void Wall::Draw(Graphics& gfx) const
{
	// divide thickness by two becuase the value passed in the thickness used for the inner bevel and the outer bevel
	bev.DrawBevelFrame(innerBounds.GetExpanded(thickness), int(thickness) / 2, gfx);
}

