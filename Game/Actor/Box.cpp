#include "Box.h"

Box::Box(const Vec2& pos)
	: RenderableActor("бр")
{
	this->pos = pos;
	color = Color::Yellow;
}
