#pragma once

#include <Actor/RenderableActor.h>

/* ��ǳ�� ����
*  - �Ϲ� O
*  - ���� +++
*  - ���� @ �Ǵ� ��
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

	virtual void Update(float deltaTime) override; // TODO: �ʿ�?
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

	// ���ٱ� ĭ ��
	int bombOffset = 1; // TODO: ������ ������ ����

	// ���� ���� ���� (CanBalloonBomb() ���)
	GameLevel* refLevel = nullptr;

	// ǳ�� ���� �÷��̾�
	Player* ownPlayer = nullptr;
};