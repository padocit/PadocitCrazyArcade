#include "Wall.h"

Wall::Wall(const Vec2& pos)
	: RenderableActor("I")
{
	this->pos = pos;
	this->color = Color::Green;
}
