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

class GameLevel;
class Balloon : public RenderableActor
{
	GENERATED_BODY(Balloon, RenderableActor)

public:
	Balloon(const Vec2& pos, GameLevel* level);

	virtual void Update(float deltaTime) override; // TODO: �ʿ�?
	virtual void Render() override;

	virtual bool Intersect(const RenderableActor& other) override;

	void SetStateBomb();

public:
	// Getter
	inline BalloonState GetBalloonState() const { return balloonState; }
	inline int BombOffset() const { return bombOffset; }

private:
	BalloonState balloonState;

	// Timer
	float elapsedTime;
	float bombTime;

	// ���ٱ� ĭ ��
	int bombOffset = 1; // TODO: ������ ������ ����

	// ���� ���� ���� (CanBalloonBomb() ���)
	GameLevel* refLevel = nullptr;
};