#pragma once

#include <Actor/RenderableActor.h>

class GameLevel;
class Player : public RenderableActor
{
	RTTI_DECLARATIONS(Player, RenderableActor)

public:
	Player(const Vec2& pos, GameLevel* level);

	virtual void Update(float deltaTime) override;

private:
	// ���� ���� ���� (CanPlayerMove() ���)
	GameLevel* refLevel = nullptr;
};