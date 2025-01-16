#include "Wall.h"

Wall::Wall(const Vec2& pos)
	: RenderableActor("H")
{
	this->pos = pos;
	this->color = Color::White;
}
