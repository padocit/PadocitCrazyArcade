#pragma once

#include <Level/Level.h>
#include <Math/Vec2.h>

/* 소코반 게임 레벨 */
class RenderableActor;
class Player;
class Block;
class Box;
class GameLevel : public Level
{
	GENERATED_BODY(GameLevel, Level)

public:
	GameLevel();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	
	// 플레이어 이동 가능 유무
	bool CanPlayerMove(const Vec2& pos);

private:
	// TODD: 게임 결과
	//bool CheckGameClear();

private:
	// 렌더링 순서 결정
	Vector<RenderableActor*> map; // walls, floors (Up-cast)
	Vector<Block*> blocks; // TODO: block <- box (상속, 업캐스팅 저장?)
	Vector<Box*> boxes;

	Player* player = nullptr;
	
	bool isGameClear = false;

};