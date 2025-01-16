#pragma once
#include <Actor/RenderableActor.h>

class Box : public RenderableActor
{
	RTTI_DECLARATIONS(Box, RenderableActor)

public:
	Box(const Vec2& pos);

};