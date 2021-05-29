#include "Wall.h"
#include <assert.h>

Wall::Wall(const RectF& innerBoundsIn, float thicknessIn, Color baseColor)
	:
	innerBounds(innerBoundsIn),
	thickness(thicknessIn),
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

