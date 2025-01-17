#include "Item.h"

Item::Item(const Vec2& pos)
	: RenderableActor("T")
{
	this->pos = pos;
}
