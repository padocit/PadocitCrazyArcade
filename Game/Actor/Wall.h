#pragma once
#include <Actor/RenderableActor.h>

class Wall : public RenderableActor
{
	RTTI_DECLARATIONS(Wall, RenderableActor)

public:
	Wall(const Vec2& pos);

};