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

	// TODO: maxCountBalloon 증가 setter
	inline void AddMaxCountBalloon() { ++maxCountBalloon; }


private:
	// 게임 레벨 참조 (CanPlayerMove() 사용)
	GameLevel* refLevel = nullptr;

	// balloon 생성 가능 개수 (아이템으로 증가)
	int maxCountBalloon; 
	int countBalloon;

	PlayerState playerState;

	float elapsedTimeLocked;
	float maxDeadTimeLocked;
	float oneDeadTimeLocked; // 1/3 maxDeadTimeLocked
	float twoDeadTimeLocked; // 2/3 maxDeadTimeLocked

};