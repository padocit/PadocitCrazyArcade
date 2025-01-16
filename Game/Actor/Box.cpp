#include "Box.h"

Box::Box(const Vec2& pos)
	: RenderableActor("#")
{
	this->pos = pos;
	color = Color::White;
}
