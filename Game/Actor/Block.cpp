#include "Block.h"

Block::Block(const Vec2& pos)
	: RenderableActor("B")
{
	this->pos = pos;
	color = Color::White;
}
