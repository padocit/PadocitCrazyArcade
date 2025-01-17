#pragma once

#include <Actor/RenderableActor.h>

/* 물풍선 상태
*  - 일반 O
*  - 터짐 +++
*  - 갇힘 @ 또는 ⓟ
*/

enum class BubbleState
{
	Normal,
	Bombed,
};

class Player;
class GameLevel;
class Bubble : public RenderableActor
{
	GENERATED_BODY(Bubble, RenderableActor)

public:
	Bubble(const Vec2& pos, GameLevel* level, Player* ownPlayer);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	virtual bool Intersect(const RenderableActor& other) override;

	void SetStateBomb();

public:
	// Getter
	inline BubbleState GetBubbleState() const { return bubbleState; }
	inline int BombOffset() const { return bombOffset; }
	inline Player& OwnPlayer() const { return *ownPlayer; }

private:
	BubbleState bubbleState;

	// Timer
	float elapsedTime;
	float bombTime;
	float destroyTime;

	// 물줄기 칸 수
	int bombOffset = 1; // TODO: 아이템 먹으면 증가

	// 게임 레벨 참조 (CanBubbleBomb() 사용)
	GameLevel* refLevel = nullptr;

	// 풍선 주인 플레이어
	Player* ownPlayer = nullptr;
};