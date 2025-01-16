#pragma once
#include <Actor/RenderableActor.h>

class Box : public RenderableActor
{
	GENERATED_BODY(Box, RenderableActor)

public:
	Box(const Vec2& pos);

};