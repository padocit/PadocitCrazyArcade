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
	Lock
};

class GameLevel;
class Balloon : public RenderableActor
{

	GENERATED_BODY(Balloon, RenderableActor)

public:
	Balloon(const Vec2& pos, GameLevel* level);

	virtual void Update(float deltaTime) override; // TODO: �ʿ�?
	virtual void Render() override;

	void SetStateBomb();
	void SetStateLock();

	inline BalloonState GetBalloonState() { return balloonState; }

private:
	BalloonState balloonState;

	// Timer
	float elapsedTime;
	float bombTime;

	// ���� ���� ���� (CanPlayerMove() ���)
	GameLevel* refLevel = nullptr;
};