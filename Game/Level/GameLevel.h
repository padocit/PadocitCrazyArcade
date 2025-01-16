#pragma once

#include <Level/Level.h>
#include <Math/Vec2.h>

/* 소코반 게임 레벨 */
class RenderableActor;
class Player;
class Block;
class Box;
class Balloon;
class GameLevel : public Level
{
	GENERATED_BODY(GameLevel, Level)

public:
	GameLevel();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	// 플레이어 이동 가능 유무
	bool CanPlayerMove(const Vec2& pos);

	// 물풍선 터짐 범위 가능 유무
	bool CanBalloonBomb(const Vec2& pos);

	// 물풍선 추가
	void AddBalloon(Balloon* balloon);

	// 물풍선-block(box) 충돌처리
	void ProcessCollisionBalloonAndBlock();

private:

	// TODD: 게임 결과
	//bool CheckGameClear();

private:
	// 렌더링 순서 결정
	Vector<RenderableActor*> map; // wall, ground (Up-cast)
	Vector<Block*> blocks; // TODO: block <- box (상속, 업캐스팅 저장?)
	Vector<Box*> boxes;
	Vector<Balloon*> balloons;

	Player* player = nullptr;

	bool isGameClear = false;

};