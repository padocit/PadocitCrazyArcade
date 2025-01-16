#pragma once

#include <Actor/RenderableActor.h>

/* 물풍선 상태
*  - 일반 O
*  - 터짐 +++
*  - 갇힘 @ 또는 ⓟ
*/

enum class BalloonState
{
	Normal,
	Bomb,
	Lock
};

class GameLevel;
class Balloon : public RenderableActor
{

	GENERATED_BODY(Balloon, RenderableActor)

public:
	Balloon(const Vec2& pos, GameLevel* level);

	virtual void Update(float deltaTime) override; // TODO: 필요?
	virtual void Render() override;

	void SetStateBomb();
	void SetStateLock();

	inline BalloonState GetBalloonState() { return balloonState; }

private:
	BalloonState balloonState;

	// Timer
	float elapsedTime;
	float bombTime;

	// 게임 레벨 참조 (CanPlayerMove() 사용)
	GameLevel* refLevel = nullptr;
};