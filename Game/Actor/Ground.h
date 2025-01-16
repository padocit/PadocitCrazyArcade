#pragma once

#include <Actor/RenderableActor.h>

class Ground : public RenderableActor
{
	RTTI_DECLARATIONS(Ground, RenderableActor)

public:
	Ground(const Vec2& pos);

};