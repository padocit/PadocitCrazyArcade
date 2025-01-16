#pragma once
#include <Actor/RenderableActor.h>

class Wall : public RenderableActor
{
	GENERATED_BODY(Wall, RenderableActor)

public:
	Wall(const Vec2& pos);

};