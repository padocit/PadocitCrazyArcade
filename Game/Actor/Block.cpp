#include "Block.h"

Block::Block(const Vec2& pos)
	: RenderableActor("��")
{
	this->pos = pos;
	color = Color::White;
}
