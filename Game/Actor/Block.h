#pragma once
#include <Actor/RenderableActor.h>

class Block : public RenderableActor
{
	GENERATED_BODY(Block, RenderableActor)

public:
	Block(const Vec2& pos);

};