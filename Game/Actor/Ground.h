#pragma once

#include <Actor/RenderableActor.h>

class Ground : public RenderableActor
{
	GENERATED_BODY(Ground, RenderableActor)

public:
	Ground(const Vec2& pos);

};