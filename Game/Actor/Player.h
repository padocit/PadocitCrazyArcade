#pragma once

#include <Actor/RenderableActor.h>
#include <Container/Vector.h>

enum class PlayerState
{
	Normal,
	Locked,
};

class GameLevel;
class Balloon;
class Player : public RenderableActor
{
	GENERATED_BODY(Player, RenderableActor)

public:
	Player(const Vec2& pos, GameLevel* level, Color color);

	virtual void Update(float deltaTime) override;

	// setter
	inline void AddCountBalloon() 
	{ 
		countBalloon = countBalloon + 1 <= maxCountBalloon ?
			countBalloon + 1 : maxCountBalloon;
	}
	inline void SubCountBalloon() 
	{ 
		countBalloon = countBalloon - 1 >= 0 ?
			countBalloon - 1 : 0;
	}

	void SetStateLocked();

	// TODO: maxCountBalloon ���� setter
	inline void AddMaxCountBalloon() { ++maxCountBalloon; }


private:
	// ���� ���� ���� (CanPlayerMove() ���)
	GameLevel* refLevel = nullptr;

	// balloon ���� ���� ���� (���������� ����)
	int maxCountBalloon; 
	int countBalloon;

	PlayerState playerState;

	float elapsedTimeLocked;
	float maxDeadTimeLocked;
	float oneDeadTimeLocked; // 1/3 maxDeadTimeLocked
	float twoDeadTimeLocked; // 2/3 maxDeadTimeLocked

};