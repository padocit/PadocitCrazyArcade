#include "Target.h"

Target::Target(const Vec2& pos)
	: RenderableActor("T")
{
	this->pos = pos;
	color = Color::Green;
}
