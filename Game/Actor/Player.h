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
	// 게임 레벨 참조 (CanPlayerMove() 사용)
	GameLevel* refLevel = nullptr;
};