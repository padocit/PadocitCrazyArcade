#include "Block.h"

Block::Block(const Vec2& pos)
	: RenderableActor("бс")
{
	this->pos = pos;
	color = Color::White;
}
