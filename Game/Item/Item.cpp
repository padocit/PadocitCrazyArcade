#include "Item.h"

Item::Item(const Vec2& pos, const char* image, Color color)
	: RenderableActor(image)
{
	this->pos = pos;
	color = color;
}
