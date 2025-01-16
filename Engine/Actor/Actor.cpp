#include "PreCompiledHeader.h"
#include "Actor.h"

Actor::Actor()
	: isActive(true), isExpired(false)
{
}

Actor::~Actor()
{
}

void Actor::Update(float deltaTime)
{
}

void Actor::Render()
{
}

void Actor::SetPos(const Vec2& newPos)
{
	pos = newPos;
}

inline Vec2 Actor::Pos() const
{
	return pos;
}
