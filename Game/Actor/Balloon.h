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
};

class Player;
class GameLevel;
class Balloon : public RenderableActor
{
	GENERATED_BODY(Balloon, RenderableActor)

public:
	Balloon(const Vec2& pos, GameLevel* level, Player* ownPlayer);

	virtual void Update(float deltaTime) override; // TODO: 필요?
	virtual void Render() override;

	virtual bool Intersect(const RenderableActor& other) override;

	void SetStateBomb();

public:
	// Getter
	inline BalloonState GetBalloonState() const { return balloonState; }
	inline int BombOffset() const { return bombOffset; }
	inline Player& OwnPlayer() const { return *ownPlayer; }

private:
	BalloonState balloonState;

	// Timer
	float elapsedTime;
	float bombTime;
	float destroyTime;

	// 물줄기 칸 수
	int bombOffset = 1; // TODO: 아이템 먹으면 증가

	// 게임 레벨 참조 (CanBalloonBomb() 사용)
	GameLevel* refLevel = nullptr;

	// 풍선 주인 플레이어
	Player* ownPlayer = nullptr;
};