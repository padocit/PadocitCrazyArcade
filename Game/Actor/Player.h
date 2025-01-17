#pragma once

#include <Actor/RenderableActor.h>
#include <Container/Vector.h>

enum class PlayerState
{
	Normal,
	Locked,
};

class InputHandler;
class GameLevel;
class Bubble;
class Player : public RenderableActor
{
	GENERATED_BODY(Player, RenderableActor)

public:
	Player(const Vec2& pos, GameLevel* level, Color color, int id = 0);

	virtual void Update(float deltaTime) override;

	void ClearPrevPosition(); // TODO: 문제 시 해당 덮어그리기 방식 수정

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void PutBubble();
	void UseItem();

	// setter
	inline void AddCountBubble() 
	{ 
		countBubble = countBubble + 1 <= maxCountBubble ?
			countBubble + 1 : maxCountBubble;
	}
	inline void SubCountBubble() 
	{ 
		countBubble = countBubble - 1 >= 0 ?
			countBubble - 1 : 0;
	}

	void SetStateLocked();

	// maxCountBubble 증가 setter
	inline void AddMaxCountBubble() { ++maxCountBubble; }


private:
	int id;
	InputHandler* playerController = nullptr;

	// 게임 레벨 참조 (CanPlayerMove() 사용)
	GameLevel* refLevel = nullptr;

	// bubble 생성 가능 개수 (아이템으로 증가)
	int maxCountBubble; 
	int countBubble;

	PlayerState playerState;

	float elapsedTimeLocked;
	float maxDeadTimeLocked;
	float oneDeadTimeLocked; // 1/3 maxDeadTimeLocked
	float twoDeadTimeLocked; // 2/3 maxDeadTimeLocked

};