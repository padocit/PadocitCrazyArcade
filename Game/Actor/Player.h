#pragma once

#include <Actor/RenderableActor.h>

class GameLevel;
class Player : public RenderableActor
{
	GENERATED_BODY(Player, RenderableActor)

public:
	Player(const Vec2& pos, GameLevel* level);

	virtual void Update(float deltaTime) override;

private:
	// ���� ���� ���� (CanPlayerMove() ���)
	GameLevel* refLevel = nullptr;
};