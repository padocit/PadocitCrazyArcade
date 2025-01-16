#pragma once

#include <Actor/RenderableActor.h>
#include <Container/Vector.h>

class GameLevel;
class Balloon;
class Player : public RenderableActor
{
	GENERATED_BODY(Player, RenderableActor)

public:
	Player(const Vec2& pos, GameLevel* level);

	virtual void Update(float deltaTime) override;

private:
	// 게임 레벨 참조 (CanPlayerMove() 사용)
	GameLevel* refLevel = nullptr;
};