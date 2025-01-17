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
	Player(const Vec2& pos, GameLevel* level);

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

	// TODO: 내가 생성한 balloon 주소 저장? (Kill/Death 기록 등에 참조?)
	// X 현재 balloon에서 player 참조하므로 없어도 될듯함
};