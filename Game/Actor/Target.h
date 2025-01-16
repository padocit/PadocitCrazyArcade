#pragma once
#include <Actor/RenderableActor.h>

class Target : public RenderableActor
{
	RTTI_DECLARATIONS(Target, RenderableActor)

public:
	Target(const Vec2& pos);

};