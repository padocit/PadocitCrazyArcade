#include "Ground.h"

Ground::Ground(const Vec2& pos)
	: RenderableActor(".")
{
	this->pos = pos;
	color = Color::White;
}
