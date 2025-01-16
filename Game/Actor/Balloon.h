#pragma once

#include <Actor/RenderableActor.h>

class Balloon : public RenderableActor
{
	GENERATED_BODY(Balloon, RenderableActor)
	
public:
	Balloon(const Vec2& pos);

	virtual void Update(float deltaTime) override;

};