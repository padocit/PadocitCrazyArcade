#include "Balloon.h"

Balloon::Balloon(const Vec2& pos)
	: RenderableActor("O")
{
	this->pos = pos;
	color = Color::Skyblue;
}

void Balloon::Update(float deltaTime)
{
}
