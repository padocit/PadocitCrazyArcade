#pragma once

#include <Actor/RenderableActor.h>

/* ��ǳ�� ����
*  - �Ϲ� O
*  - ���� +++
*  - ���� @ �Ǵ� ��
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

	// ���ٱ� ĭ ��
	int bombOffset = 1; // TODO: ������ ������ ����

	// ���� ���� ���� (CanBubbleBomb() ���)
	GameLevel* refLevel = nullptr;

	// ǳ�� ���� �÷��̾�
	Player* ownPlayer = nullptr;
};