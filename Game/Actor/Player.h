#pragma once

#include <Actor/RenderableActor.h>
#include <Container/Vector.h>

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

	// TODO: maxCountBalloon ���� setter
	inline void AddMaxCountBalloon() { ++maxCountBalloon; }


private:
	// ���� ���� ���� (CanPlayerMove() ���)
	GameLevel* refLevel = nullptr;

	// balloon ���� ���� ���� - ���������� ����
	int maxCountBalloon; 
	int countBalloon;

	// TODO: ���� ������ balloon �ּ� ����? (Kill/Death ��� � ����?)
	// X ���� balloon���� player �����ϹǷ� ��� �ɵ���
	
};